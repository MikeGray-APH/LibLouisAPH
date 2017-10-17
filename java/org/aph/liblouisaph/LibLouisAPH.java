/*

   Copyright 2017 American Printing House for the Blind Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

package org.aph.liblouisaph;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;
import java.util.Properties;

/**
 * The <code>LibLouisAPH</code> class contains static methods for inferfacing
 * with the LibLouisAPH library.
 */
public class LibLouisAPH
{

/******************************************************************************/

	private static String tmpDirName = null;

	private static String getTmpDirName()
	{
		if(tmpDirName == null)
		{
			try
			{
				File tmpDirFile = Files.createTempDirectory("llaph").toFile();
				tmpDirFile.deleteOnExit();
				tmpDirName = tmpDirFile.getPath();
			}
			catch(IOException exception)
			{
				tmpDirName = "." + File.separator + "llaph";
				String tmpDir = System.getProperty("java.io.tmpdir");
				if(tmpDir != null)
					tmpDirName = tmpDir + File.separator + "llaph";
				File tmpDirFile = new File(tmpDirName);
				tmpDirFile.mkdir();
				tmpDirFile.deleteOnExit();
			}
		}

		return tmpDirName;
	}

	/**
	 * Loads the native liblouisAPH library stored in the jar file.
	 *
	 * @throws IOException if unable to load internal library
	 */
	public static void loadLibrary() throws IOException
	{
		Properties properties = new Properties();
		properties.load(LibLouisAPH.class.getResourceAsStream("/properties"));
		if(properties == null)
			throw new IOException("unable to load jar properties");
		String dllName = properties.getProperty("Library-Name");
		if(dllName == null)
			throw new IOException("unable to find Library-Name in jar properties");
		InputStream dllInputStream = LibLouisAPH.class.getResourceAsStream("/" + dllName);
		if(dllInputStream == null)
			throw new IOException("unable to find /" + dllName + " in jar");

		String libName = getTmpDirName() + File.separator + dllName;
		File libFile = new File(libName);
		if(libFile.isFile())
			return;
		Files.copy(dllInputStream, libFile.toPath(), StandardCopyOption.REPLACE_EXISTING);
		dllInputStream.close();
		libFile.deleteOnExit();

		System.load(libName);
		louis_set_lookup_hook();
		louis_set_log_callback();
	}

	/**
	 * Loads the native liblouisAPH library <code>libraryName</code>.
	 *
	 * <p>The library name may not contain a system dependent prefix, suffix,
	 * or path.  The library is located in a system dependent mannor.</p>
	 *
	 * @param  libraryName  name of the library to be loaded
	 */
	public static void loadLibrary(String libraryName)
	{
		System.loadLibrary(libraryName);
		louis_set_log_callback();
		tmpDirName = null;
	}

	/**
	 * Loads the native liblouisAPH library file <code>libraryName</code>.
	 *
	 * <p>The library file name must be absolute.</p>
	 *
	 * @param  libraryName  file name of the library to be loaded
	 */
	public static void loadLibraryFullName(String libraryName)
	{
		System.load(libraryName);
		louis_set_log_callback();
		tmpDirName = null;
	}

/******************************************************************************/

	private static native void louis_set_lookup_hook();

	private static int lookupHook(char path[], String fileName)
	{
		if(tmpDirName == null)
			return 0;

		String tablesDirName = getTmpDirName() + File.separator + "tables";
		File tablesDir = new File(tablesDirName);
		if(!tablesDir.isDirectory())
		{
			tablesDir.mkdir();
			tablesDir.deleteOnExit();
			addPaths(tablesDirName);
		}

		String tableName = tablesDirName + File.separator + fileName;
		File tableFile = new File(tableName);
		if(!tableFile.isFile())
		{
			InputStream inputStream = new LibLouisAPH().getClass().getResourceAsStream("/tables/" + fileName);
			if(inputStream == null)
				return 0;

			try
			{
				Files.copy(inputStream, tableFile.toPath(), StandardCopyOption.REPLACE_EXISTING);
			}
			catch(IOException exception)
			{
				return 0;
			}
			finally
			{
				tableFile.deleteOnExit();
			}
		}

		int length = tableName.length();
		if(length > path.length - 1)
			length = path.length - 1;
		tableName.getChars(0, length, path, 0);
		path[length] = 0;

		return 1;
	}

/******************************************************************************/

	private static native void louis_set_log_callback();

	private static LogCallback logCallback;

	private static void logCallback(int logLevel, String logMessage)
	{
		if(logCallback != null)
			logCallback.logCallback(logLevel, logMessage);
	}

	/**
	 * Gets the <code>LogCallback</code> object that is receiving log
	 * messages from the library.
	 *
	 * @return the currently set <code>LogCallback</code> object
	 */
	public static LogCallback getLogCallback()
	{
		return logCallback;
	}

	/**
	 * Sets the <code>LogCallback</code> object that is to receive log
	 * messages from the library.
	 *
	 * @param  logCallback  the <code>LogCallback</code> object to be set
	 *
	 * @return the previous set <code>LogCallback</code> object
	 */
	public static LogCallback setLogCallback(LogCallback logCallback)
	{
		LogCallback prvLogCallback = LibLouisAPH.logCallback;
		LibLouisAPH.logCallback = logCallback;
		return prvLogCallback;
	}

/******************************************************************************/

	private static native int louis_get_version_length();
	private static native int louis_get_version(char version[]);

	/**
	 * Gets the library version.
	 *
	 * @return the library version string
	 */
	public static String getVersion()
	{
		int versionLength = louis_get_version_length();
		char versionChars[] = new char[versionLength + 1];
		versionLength = louis_get_version(versionChars);
		return new String(versionChars, 0, versionLength);
	}

/******************************************************************************/

	private static native int louis_get_paths_length();
	private static native int louis_get_paths(char paths[]);
	private static native int louis_set_paths(String paths);
	private static native int louis_add_paths(String paths);

	/**
	 * Gets the current table path list.
	 *
	 * @return the current table path list string
	 */
	public static String getPaths()
	{
		int pathsLength = louis_get_paths_length();
		if(pathsLength == 0)
			return null;
		char pathsChars[] = new char[pathsLength + 1];
		pathsLength = louis_get_paths(pathsChars);
		if(pathsLength == 0)
			return null;
		return new String(pathsChars, 0, pathsLength);
	}

	/**
	 * Sets the current table path list to <code>paths</code>.
	 *
	 * @param  paths  the new path list
	 *
	 * @return the number of characters of the new current path list
	 */
	public static int setPaths(String paths)
	{
		return louis_set_paths(paths);
	}

	/**
	 * Appends <code>paths</code> to the current table path list with the
	 * system path separator.
	 *
	 * @param  paths  list to be appended
	 *
	 * @return the number of characters of the new current path list
	 */
	public static int addPaths(String paths)
	{
		return louis_add_paths(paths);
	}

/******************************************************************************/

	private static native int louis_translate(char dots[], String chars, String tables_name, String conversion_name, int directionInt, int chars_to_dots_map[], int dots_to_chars_map[], int cursor_map[]);

	private static String translate(String charsString, int dotsMax, String tables, String conversion, boolean forward, int charsToDotsMap[], int dotsToCharsMap[], int cursorMap[])
	{
		char dotsChars[] = new char[dotsMax];

		int charsToDotsMapInts[] = null;
		if(charsToDotsMap != null)
			charsToDotsMapInts = new int[charsString.length()];

		int dotsToCharsMapInts[] = null;
		if(dotsToCharsMap != null)
			dotsToCharsMapInts = new int[dotsMax];

		int length = 0;
		if(forward)
			length = louis_translate(dotsChars, charsString, tables, conversion, +1, charsToDotsMapInts, dotsToCharsMapInts, cursorMap);
		else
			length = louis_translate(dotsChars, charsString, tables, conversion, -1, charsToDotsMapInts, dotsToCharsMapInts, cursorMap);

		if(length <= 0)
			return null;

		if(charsToDotsMapInts != null)
		for(int i = 0; i < charsString.length() && i < charsToDotsMap.length; i++)
			charsToDotsMap[i] = charsToDotsMapInts[i];

		if(dotsToCharsMapInts != null)
		for(int i = 0; i < length && i < dotsToCharsMap.length; i++)
			dotsToCharsMap[i] = dotsToCharsMapInts[i];

		return new String(dotsChars, 0, length);
	}

	/**
	 * Returns the forward translation of <code>charsString</code>.
	 *
	 * @param charsString     text to be translated
	 * @param cellsMax        maximum number of cells in translation
	 * @param tables          name of translation tables
	 * @param conversion      name of conversion table
	 * @param charsToDotsMap  array to hold mapping from text to braille
	 * @param dotsToCharsMap  array to hold mapping from braille to text
	 * @param cursorMap       array holding cursor position to be mapped
	 *
	 * @return <code>String</code> containing the forward translation of
	 *          <code>charsString</code>, or <code>null</code> if an error
	 *          occurred
	 */
	public static String translateForward(String charsString, int cellsMax, String tables, String conversion, int charsToDotsMap[], int dotsToCharsMap[], int cursorMap[])
	{
		return translate(charsString, cellsMax, tables, conversion, true, charsToDotsMap, dotsToCharsMap, cursorMap);
	}

	/**
	 * Returns the backward translation of <code>cellsString</code>.
	 *
	 * @param cellsString     braille to be translated
	 * @param charsMax        maximum number of characters in translation
	 * @param tables          name of translation tables
	 * @param conversion      name of conversion table
	 * @param charsToDotsMap  array to hold mapping from text to braille
	 * @param dotsToCharsMap  array to hold mapping from braille to text
	 * @param cursorMap       array holding cursor position to be mapped
	 *
	 * @return <code>String</code> containing the backward translation of
	 *          <code>cellsString</code>, or <code>null</code> if an error
	 *          occurred
	 */
	public static String translateBackward(String cellsString, int charsMax, String tables, String conversion, int dotsToCharsMap[], int charsToDotsMap[], int cursorMap[])
	{
		return translate(cellsString, charsMax, tables, conversion, false, dotsToCharsMap, charsToDotsMap, cursorMap);
	}

/******************************************************************************/

	private static native int louis_convert(char cells[], String conversion_name, int directionInt);

	private static String convert(String cellsString, String conversion, boolean forward)
	{
		if(conversion == null)
			return null;

		char cellsChars[] = new char[cellsString.length()];
		cellsString.getChars(0, cellsString.length(), cellsChars, 0);

		int status;
		if(forward)
			status = louis_convert(cellsChars, conversion, +1);
		else
			status = louis_convert(cellsChars, conversion, -1);

		if(status <= 0)
			return null;

		return new String(cellsChars, 0, cellsString.length());
	}

	/**
	 * Returns the forward conversion of <code>cellsString</code>.
	 *
	 * @param cellsString  braille to be forward converted
	 * @param conversion   name of conversion table
	 *
	 * @return <code>String</code> containing the forward conversion of
	 *          <code>cellsString</code>, or <code>null</code> if an error
	 *          occurred
	 */
	public static String convertForward(String cellsString, String conversion)
	{
		return convert(cellsString, conversion, true);
	}

	/**
	 * Returns the backward conversion of <code>cellsString</code>.
	 *
	 * @param cellsString  braille to be backward converted
	 * @param conversion   name of conversion table
	 *
	 * @return <code>String</code> containing the backward conversion of
	 *          <code>cellsString</code>, or <code>null</code> if an error
	 *          occurred
	 */
	public static String convertBackward(String cellsString, String conversion)
	{
		return convert(cellsString, conversion, false);
	}

/******************************************************************************/

}
