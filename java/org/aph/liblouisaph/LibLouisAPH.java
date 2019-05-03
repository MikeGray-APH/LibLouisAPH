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
import java.util.Arrays;
import java.util.Properties;

/**
 * The {@code LibLouisAPH } class contains static methods for inferfacing with
 * the LibLouisAPH library.
 */
public class LibLouisAPH
{
	private static Object llaphLock = new Object();

/******************************************************************************/

	/**
	 * Returns the Implementation-Version from the jar's manifest.
	 *
	 * @return  the Implementation-Version string
	 */
	public static String getImplementationVersion()
	{
		return LibLouisAPH.class.getPackage().getImplementationVersion();
	}

/******************************************************************************/

	private static String internalLibraryName = null;
	private static String externalLibraryName = null;
	private static String systemLibraryName = null;
	private static String internalTablePath = null;
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
	* Returns the current internal table path
	*
	* @return  the current internal table path
	*/
	public static String getInternalTablePath()
	{
		return internalTablePath;
	}

	/**
	 * Sets the table path for the tables stored in the jar file.
	 *
	 * @param  tablePath  path to the table directory to be used
	 */
	public static void setInternalTablePath(String tablePath)
	{
		if(tablePath == null)
		{
			internalTablePath = null;
			return;
		}

		internalTablePath = new String(tablePath);

		/*   normalize slashes   */
		if(internalTablePath.charAt(0) != '/')
			internalTablePath = "/" + internalTablePath;

		synchronized(llaphLock)
		{
			louis_set_lookup_hook();
		}
	}


	/**
	 * Sets the table path for the tables stored in the jar file using the
	 * {@code Table-Path } property from the {@code /properties }
	 * file from the jar file.
	 *
	 * @throws IOException  if unable to load internal library
	 */
	public static void setInternalTablePath() throws IOException
	{
		Properties properties = new Properties();
		properties.load(LibLouisAPH.class.getResourceAsStream("/liblouisaph.properties"));
		if(properties == null)
			throw new IOException("unable to load jar liblouisaph.properties");
		String tablePath = properties.getProperty("Table-Path");
		if(tablePath == null)
			throw new IOException("unable to find Table-Path in jar liblouisaph.properties");
		setInternalTablePath(tablePath);
	}

	/**
	* Returns the current internal library name
	*
	* @return the current internal library name
	*/
	public static String getInternalLibraryName()
	{
		return internalLibraryName;
	}

	/**
	 * Loads the native liblouisAPH library {@code libraryName } stored in
	 * the jar file.
	 *
	 * @param  libraryName  name of the library to be loaded
	 *
	 * @throws IOException  if unable to load internal library
	 */
	public static void loadLibraryInternal(String libraryName) throws IOException
	{
		internalLibraryName = new String(libraryName);

		/*   normalize slashes   */
		if(internalLibraryName.charAt(0) != '/')
			internalLibraryName = "/" + internalLibraryName;

		InputStream libraryInputStream = LibLouisAPH.class.getResourceAsStream(internalLibraryName);
		if(libraryInputStream == null)
			throw new IOException("unable to find " + internalLibraryName + " in jar");

		int index = internalLibraryName.lastIndexOf('/');
		String libraryFullName = getTmpDirName() + File.separator + internalLibraryName.substring(index + 1);
		File libraryFile = new File(libraryFullName);
		if(libraryFile.isFile())
			return;
		Files.copy(libraryInputStream, libraryFile.toPath(), StandardCopyOption.REPLACE_EXISTING);
		libraryInputStream.close();
		libraryFile.deleteOnExit();

		loadLibraryExternal(libraryFullName);
	}

	/**
	 * Loads the native liblouisAPH library stored in the jar file using the
	 * {@code Library-Name } property from the {@code /properties } file
	 * from the jar file.
	 *
	 * @throws IOException  if unable to load internal library
	 */
	public static void loadLibraryInternal() throws IOException
	{
		Properties properties = new Properties();
		properties.load(LibLouisAPH.class.getResourceAsStream("/liblouisaph.properties"));
		if(properties == null)
			throw new IOException("unable to load jar liblouisaph.properties");
		String libraryName = properties.getProperty("Library-Name");
		if(libraryName == null)
			throw new IOException("unable to find Library-Name in jar liblouisaph.properties");
		loadLibraryInternal(libraryName);
	}

	/**
	* Returns the current external library name
	*
	* @return  the current external library name
	*/
	public static String getExternalLibraryName()
	{
		return externalLibraryName;
	}

	/**
	 * Loads the native liblouisAPH library file {@code libraryName }.
	 *
	 * <p>The library file name must be absolute.</p>
	 *
	 * @param  libraryName  file name of the library to be loaded
	 */
	public static void loadLibraryExternal(String libraryName)
	{
		System.load(libraryName);
		externalLibraryName = libraryName;

		synchronized(llaphLock)
		{
			louis_set_log_callback();
		}
	}

	/**
	* Returns the current system library name
	*
	* @return  the current system library name
	*/
	public static String getSystemLibraryName()
	{
		return systemLibraryName;
	}

	/**
	 * Loads the native liblouisAPH library {@code libraryName }.
	 *
	 * <p>The library name may not contain a system dependent prefix, suffix,
	 * or path.  The library is located in a system dependent mannor.</p>
	 *
	 * @param  libraryName  name of the library to be loaded
	 */
	public static void loadLibrarySystem(String libraryName)
	{
		System.loadLibrary(libraryName);
		systemLibraryName = libraryName;

		synchronized(llaphLock)
		{
			louis_set_log_callback();
		}

	}

/******************************************************************************/

	private static native void louis_set_lookup_hook();

	private static int lookupHook(char path[], String fileName)
	{
		if(internalTablePath == null)
			return 0;

		String tablesDirName = getTmpDirName() + File.separator + internalTablePath;
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
			InputStream inputStream = new LibLouisAPH().getClass().getResourceAsStream(internalTablePath + "/" + fileName);
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
	 * Returns the {@code LogCallback } object that is receiving log
	 * messages from the library.
	 *
	 * @return  the currently set {@code LogCallback } object
	 */
	public static LogCallback getLogCallback()
	{
		return logCallback;
	}

	/**
	 * Sets the {@code LogCallback } object that is to receive log messages
	 * from the library.
	 *
	 * @param  logCallback  the {@code LogCallback } object to be set
	 *
	 * @return  the previous set {@code LogCallback } object
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
	 * Returns the library version.
	 *
	 * @return the library version string
	 */
	public static String getVersion()
	{
		int versionLength;
		char versionChars[];

		synchronized(llaphLock)
		{
			versionLength = louis_get_version_length();
			if(versionLength == 0)
				return null;
			versionChars = new char[versionLength + 1];
			versionLength = louis_get_version(versionChars);
		}
		if(versionLength == 0 || versionChars == null)
			return null;

		return new String(versionChars, 0, versionLength);
	}

/******************************************************************************/

	private static native int louis_get_paths_length();
	private static native int louis_get_paths(char paths[]);
	private static native int louis_set_paths(String paths);
	private static native int louis_add_paths(String paths);

	/**
	 * Returns the current table path list.
	 *
	 * @return  the current table path list string
	 */
	public static String getPaths()
	{
		int pathsLength;
		char pathsChars[];

		synchronized(llaphLock)
		{
			pathsLength = louis_get_paths_length();
			if(pathsLength == 0)
				return null;
			pathsChars = new char[pathsLength + 1];
			pathsLength = louis_get_paths(pathsChars);
		}
		if(pathsLength == 0 || pathsChars == null)
			return null;

		return new String(pathsChars, 0, pathsLength);
	}

	/**
	 * Sets the current table path list to {@code paths }.
	 *
	 * @param  paths  the new path list
	 *
	 * @return  the number of characters of the new current path list
	 */
	public static int setPaths(String paths)
	{
		int result;
		synchronized(llaphLock)
		{
			result = louis_set_paths(paths);
		}
		return result;
	}

	/**
	 * Appends {@code paths } to the current table path list with the system
	 * path separator.
	 *
	 * @param  paths  list to be appended
	 *
	 * @return  the number of characters of the new current path list
	 */
	public static int addPaths(String paths)
	{
		int result;
		synchronized(llaphLock)
		{
			result = louis_add_paths(paths);
		}
		return result;
	}

/******************************************************************************/

	private static native int louis_translate(char dots[], String chars, String tables_name, String conversion_name, int directionInt, int chars_to_dots_map[], int dots_to_chars_map[], int cursor_map[]);

	private static String translate(String charsString, int dotsMax, String tables, String conversion, boolean forward, int charsToDotsMap[], int dotsToCharsMap[], int cursorMap[])
	{
		char dotsChars[] = new char[dotsMax];

		boolean mapping = false;
		if(charsToDotsMap != null && dotsToCharsMap != null)
			mapping = true;
		if(charsToDotsMap == null && dotsToCharsMap != null)
			logCallback(LogCallback.LOG_WARNING, "dotsToCharsMap ignored");
		if(charsToDotsMap != null && dotsToCharsMap == null)
			logCallback(LogCallback.LOG_WARNING, "charsToDotsMap ignored");

		int charsToDotsMapInts[] = null;
		int dotsToCharsMapInts[] = null;
		if(mapping)
		{
			charsToDotsMapInts = new int[charsString.length()];
			dotsToCharsMapInts = new int[dotsMax];
		}

		int length = 0;
		synchronized(llaphLock)
		{
			if(forward)
				length = louis_translate(dotsChars, charsString, tables, conversion, +1, charsToDotsMapInts, dotsToCharsMapInts, cursorMap);
			else
				length = louis_translate(dotsChars, charsString, tables, conversion, -1, charsToDotsMapInts, dotsToCharsMapInts, cursorMap);
		}
		if(length <= 0)
			return null;

		if(mapping)
		{
			for(int i = 0; i < charsString.length() && i < charsToDotsMap.length; i++)
				charsToDotsMap[i] = charsToDotsMapInts[i];
			for(int i = 0; i < length && i < dotsToCharsMap.length; i++)
				dotsToCharsMap[i] = dotsToCharsMapInts[i];
		}

		return new String(dotsChars, 0, length);
	}

	/**
	 * Returns the forward translation of {@code charsString }.
	 *
	 * @param charsString     text to be translated
	 * @param cellsMax        maximum number of cells in translation
	 * @param tables          name of translation tables
	 * @param conversion      name of conversion table
	 * @param charsToDotsMap  array to hold mapping from text to braille
	 * @param dotsToCharsMap  array to hold mapping from braille to text
	 * @param cursorMap       array holding cursor position to be mapped
	 *
	 * @return  {@code String } containing the forward translation of
	 *          {@code charsString }, or {@code null } if an error
	 *          occurred
	 */
	public static String translateForward(String charsString, int cellsMax, String tables, String conversion, int charsToDotsMap[], int dotsToCharsMap[], int cursorMap[])
	{
		return translate(charsString, cellsMax, tables, conversion, true, charsToDotsMap, dotsToCharsMap, cursorMap);
	}

	/**
	 * Returns the backward translation of {@code cellsString }.
	 *
	 * @param cellsString     braille to be translated
	 * @param charsMax        maximum number of characters in translation
	 * @param tables          name of translation tables
	 * @param conversion      name of conversion table
	 * @param charsToDotsMap  array to hold mapping from text to braille
	 * @param dotsToCharsMap  array to hold mapping from braille to text
	 * @param cursorMap       array holding cursor position to be mapped
	 *
	 * @return  {@code String } containing the backward translation of
	 *          {@code cellsString }, or {@code null } if an error
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
		synchronized(llaphLock)
		{
			if(forward)
				status = louis_convert(cellsChars, conversion, +1);
			else
				status = louis_convert(cellsChars, conversion, -1);
		}
		if(status <= 0)
			return null;

		return new String(cellsChars, 0, cellsString.length());
	}

	/**
	 * Returns the forward conversion of {@code cellsString }.
	 *
	 * @param cellsString  braille to be forward converted
	 * @param conversion   name of conversion table
	 *
	 * @return  {@code String } containing the forward conversion of
	 *          {@code cellsString }, or {@code null } if an error
	 *          occurred
	 */
	public static String convertForward(String cellsString, String conversion)
	{
		return convert(cellsString, conversion, true);
	}

	/**
	 * Returns the backward conversion of {@code cellsString }.
	 *
	 * @param cellsString  braille to be backward converted
	 * @param conversion   name of conversion table
	 *
	 * @return  {@code String } containing the backward conversion of
	 *          {@code cellsString }, or {@code null } if an error
	 *          occurred
	 */
	public static String convertBackward(String cellsString, String conversion)
	{
		return convert(cellsString, conversion, false);
	}

/******************************************************************************/

	/**
	 * Returns a {@code Translation } object of {@code input}.
	 *
	 * @param input           text to be translated
	 * @param tables          names of translation tables
	 * @param conversion      name of conversion table, or {@code null }
	 * @param forward         {@code true } for forward translation, else
	 *                        backward translation
	 * @param mapping         {@code true } to include mappings
	 * @param cursor          cursor position to be mapped, or -1 to ignore
	 *
	 * @return  {@code Translation } object containing the translation,
	 *          mappings, and cursor positions, or {@code null } if an error
	 *          occurred
	 */
	public static Translation translate(String input, String tables, String conversion, boolean forward, boolean mapping, int cursor)
	{
		char output[] = new char[input.length() * 4];

		int inputToOutputMap[] = null;
		int outputToInputMap[] = null;
		if(mapping)
		{
			inputToOutputMap = new int[input.length()];
			outputToInputMap = new int[output.length];
		}

		int cursorMap[] = null;
		if(cursor >= 0)
		{
			cursorMap = new int[1];
			cursorMap[0] = cursor;
		}

		int length = 0;
		synchronized(llaphLock)
		{
			if(forward)
				length = louis_translate(output, input, tables, conversion, +1, inputToOutputMap, outputToInputMap, cursorMap);
			else
				length = louis_translate(output, input, tables, conversion, -1, inputToOutputMap, outputToInputMap, cursorMap);
		}
		if(length <= 0)
			return null;

		if(length >= output.length)
		{
			logCallback(LogCallback.LOG_WARNING, "increasing output length to " + length);
			output = new char[length];
			if(mapping)
				outputToInputMap = new int[output.length];
			if(cursorMap != null)
				cursorMap[0] = cursor;

			length = 0;
			synchronized(llaphLock)
			{
				if(forward)
					length = louis_translate(output, input, tables, conversion, +1, inputToOutputMap, outputToInputMap, cursorMap);
				else
					length = louis_translate(output, input, tables, conversion, -1, inputToOutputMap, outputToInputMap, cursorMap);
			}
			if(length <= 0)
				return null;
		}

		Translation translation = new Translation();
		translation.tables = tables;
		translation.conversion = conversion;

		if(forward)
		{
			translation.chars = input;
			translation.dots = new String(output, 0, length);

			if(inputToOutputMap != null)
				translation.charsToDotsMap = inputToOutputMap;
			if(outputToInputMap != null)
				translation.dotsToCharsMap = Arrays.copyOf(outputToInputMap, length);

			if(cursorMap != null)
			{
				translation.cursorChars = cursor;
				translation.cursorDots = cursorMap[0];
			}
			else
				translation.cursorChars =
				translation.cursorDots = -1;
		}
		else
		{
			translation.chars = new String(output, 0, length);
			translation.dots = input;

			if(inputToOutputMap != null)
				translation.charsToDotsMap = Arrays.copyOf(outputToInputMap, length);
			if(outputToInputMap != null)
				translation.dotsToCharsMap = inputToOutputMap;

			if(cursorMap != null)
			{
				translation.cursorChars = cursorMap[0];
				translation.cursorDots = cursor;
			}
			else
				translation.cursorChars =
				translation.cursorDots = -1;
		}

		return translation;
	}

/******************************************************************************/

}
