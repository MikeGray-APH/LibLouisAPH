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

/******************************************************************************/

import java.io.IOException;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;

import org.aph.liblouisaph.LibLouisAPH;
import org.aph.liblouisaph.LogCallback;

public class TestJar
{
	static private PrintStream output, console;

/******************************************************************************/

	private static void setLogCallback()
	{
		LogCallback logCallback = new LogCallback()
		{
			public void logCallback(int logLevel, String logMessage)
			{
				switch(logLevel)
				{
				case 0:
					output.println();
					output.flush();
					return;

				case LogCallback.LOG_ALL:      output.print("ALL:  ");      break;
				case LogCallback.LOG_TRACE:    output.print("TRACE:  ");    break;
				case LogCallback.LOG_DEBUG:    output.print("DEBUG:  ");    break;
				case LogCallback.LOG_INFO:     output.print("INFO:  ");     break;
				case LogCallback.LOG_WARNING:  output.print("WARNING:  ");  break;
				case LogCallback.LOG_ERROR:    output.print("ERROR:  ");    break;
				case LogCallback.LOG_FATAL:    output.print("FATAL:  ");    break;
				}
				output.println(logMessage);
				output.flush();
			}
		};
		LibLouisAPH.setLogCallback(logCallback);
	}

	private static void getVersions()
	{
		output.println("getImplementationVersion  = " + LibLouisAPH.getImplementationVersion());
		output.println("getVersion                = " + LibLouisAPH.getVersion());
		output.flush();
	}

/******************************************************************************/

	private static void testGetPaths(String result, boolean doOutput)
	{
		output.print("getPaths                  = ");
		output.flush();
		if(doOutput)
		if(console != output)
			console.print("getPaths:  ");

		String paths = LibLouisAPH.getPaths();
		if(paths == null)
		if(result == null)
		{
			output.println();
			output.flush();
			if(console != output)
				console.println("PASS");
			return;
		}
		else
		{
			output.println("ERROR:  getPaths null");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  getPaths");
		}
		else if(result == null)
		{
			output.println("ERROR:  getPaths !null");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  getPaths");
		}

		output.println(paths);
		output.flush();
		if(!paths.equals(result))
		{
			output.println("ERROR:  getPaths \"" + result + "\"");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  getPaths");
		}
		if(console != output)
			console.println("PASS");
	}

	private static void testSetPaths(String paths)
	{
		output.println("setPaths                 := " + paths);
		output.flush();
		if(console != output)
		{
			console.print("setPaths:  ");
			console.flush();
		}
		if(LibLouisAPH.setPaths(paths) == 0)
		{
			output.println("ERROR:  setPaths");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  setPaths");
		}

		testGetPaths(paths, false);
	}

	private static void testAddPaths(String paths, String result)
	{
		output.println("addPaths                 := " + paths);
		output.flush();
		if(console != output)
		{
			console.print("addPaths:  ");
			console.flush();
		}
		if(LibLouisAPH.addPaths(paths) == 0)
		{
			output.println("ERROR:  addPaths");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  addPaths");
		}

		testGetPaths(result, false);
	}

/******************************************************************************/

	private static void testTranslation(String chars, String result, String table, String conversion, int charsToDots[], int dotsToChars[], int cursors[])
	{
		int charsToDotsMap[] = new int[0x100];
		int dotsToCharsMap[] = new int[0x100];
		int cursorMap[] = new int[1];

		String forward, backward;

		output.print("translateForward          = ");
		output.flush();
		if(console != output)
		{
			console.print("translateForward:  ");
			console.flush();
		}
		cursorMap[0] = cursors[0];
		forward = LibLouisAPH.translateForward(chars, chars.length() * 7, table, conversion, charsToDotsMap, dotsToCharsMap, cursorMap);
		if(forward == null)
		{
			output.println();
			output.println("ERROR:  translateForward null");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateForward");
		}
		output.println(forward);
		output.flush();
		if(!forward.equals(result))
		{
			output.println("ERROR:  translateForward translation");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateForward");
		}
		for(int i = 0; i < 13; i++)
		if(charsToDotsMap[i] != charsToDots[i])
		{
			output.println("ERROR:  translateForward charsToDotsMap");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateForward");
		}
		for(int i = 0; i < 20; i++)
		if(dotsToCharsMap[i] != dotsToChars[i])
		{
			output.println("ERROR:  translateForward dotsToCharsMap");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateForward");
		}
		if(cursorMap[0] != cursors[1])
		{
			output.println("ERROR:  translateForward cursor");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateForward");
		}
		if(console != output)
			console.println("PASS");


		output.print("translateBackward         = ");
		output.flush();
		if(console != output)
		{
			console.print("translateBackward:  ");
			console.flush();
		}
		cursorMap[0] = cursors[2];
		backward = LibLouisAPH.translateBackward(forward, forward.length() * 7, table, conversion, charsToDotsMap, dotsToCharsMap, cursorMap);
		if(backward == null)
		{
			output.println();
			output.println("ERROR:  translateBackward null");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateBackward");
		}
		output.println(backward);
		output.flush();
		if(!backward.equals(chars))
		{
			output.println("ERROR:  translateBackward translation");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateBackward");
		}
		for(int i = 0; i < 20; i++)
		if(charsToDotsMap[i] != dotsToChars[i])
		{
			output.println("ERROR:  translateBackward charsToDotsMap");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateBackward");
		}
		for(int i = 0; i < 13; i++)
		if(dotsToCharsMap[i] != charsToDots[i])
		{
			output.println("ERROR:  translateBackward dotsToCharsMap");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateBackward");
		}
		if(cursorMap[0] != cursors[3])
		{
			output.println("ERROR:  translateBackward cursor");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateBackward");
		}
		if(console != output)
			console.println("PASS");
	}

	private static void testConversion(String cells, String result, String conversion)
	{
		String forward, backward;

		output.print("convertForward            = ");
		output.flush();
		if(console != output)
		{
			console.print("convertForward:  ");
			console.flush();
		}
		forward = LibLouisAPH.convertForward(cells, conversion);
		if(forward == null)
		{
			output.println();
			output.println("ERROR:  convertForward null");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  convertForward");
		}
		output.println(forward);
		output.flush();
		if(!forward.equals(result))
		{
			output.println("ERROR:  convertForward conversion");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  convertForward");
		}
		if(console != output)
			console.println("PASS");


		output.print("convertBackward           = ");
		output.flush();
		if(console != output)
		{
			console.print("convertBackward:  ");
			console.flush();
		}
		backward = LibLouisAPH.convertBackward(forward, conversion);
		if(backward == null)
		{
			output.println();
			output.println("ERROR:  null");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  convertBackward null");
		}
		output.println(backward);
		output.flush();
		if(!backward.equals(cells))
		{
			output.println("ERROR:  convertBackward conversion");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  convertBackward");
		}
		if(console != output)
			console.println("PASS");
	}

	private static void doTests()
	{
		getVersions();
		testGetPaths(null, true);
		testSetPaths("tables");
		testAddPaths("test/tables", "tables:test/tables");
		testTranslation(
			"x xx xxx xx x",
			"\u2815\u282a\u2800\u2815\u282a\u2815\u282a\u2800\u2815\u2815\u282a\u282a\u2800\u2815\u282a\u2815\u282a\u2800\u2815\u282a",
			"link.rst",
			null,
			new int[]{0,2,3,5,7,8,8,8,12,13,15,17,18},
			new int[]{0,0,1,2,2,3,3,4,5,5,5,5,8,9,9,10,10,11,12,12},
			new int[]{7,8,8,5});
		testConversion(
			"\u2815\u282a\u2800\u2815\u282a\u2815\u282a\u2800\u2815\u2815\u282a\u282a\u2800\u2815\u282a\u2815\u282a\u2800\u2815\u282a",
			">< ><>< >><< ><>< ><",
			"link.cvt");

		if(console != output)
		{
			console.println();
			output.close();
		}
		else
			output.println();
	}

/******************************************************************************/

	private static void testInternal() throws IOException, UnsupportedEncodingException
	{
		String libraryName, tablePath;

		console = new PrintStream(System.out, true, "UTF-8");
		try
		{
			output = new PrintStream("build/test/output-jar-internal.txt", "UTF-8");
		}
		catch(IOException exception)
		{
			output = console;
		}

		output.println("testing jar internal");
		output.println();
		output.flush();
		if(console != output)
			console.println("testing jar internal");

		LibLouisAPH.loadLibraryInternal();
		LibLouisAPH.setInternalTablePath();
		setLogCallback();

		output.print("getInternalLibraryName    = ");
		output.flush();
		if(console != output)
		{
			console.print("getInternalLibraryName:  ");
			console.flush();
		}
		libraryName = LibLouisAPH.getInternalLibraryName();
		output.println(libraryName);
		output.flush();
		if(!libraryName.equals("/liblouisAPH-jni.so"))
		{
			output.println("ERROR:  getInternalLibraryName");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  getInternalLibraryName");
		}
		if(console != output)
		{
			console.println("PASS");
			console.flush();
		}

		output.print("getInternalTablePath      = ");
		output.flush();
		if(console != output)
		{
			console.print("getInternalTablePath:  ");
			console.flush();
		}
		tablePath = LibLouisAPH.getInternalTablePath();
		output.println(tablePath);
		output.flush();
		if(!tablePath.equals("/tables"))
		{
			output.println("ERROR:  getInternalTablePath");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  getInternalTablePath");
		}
		if(console != output)
		{
			console.println("PASS");
			console.flush();
		}

		doTests();
	}

	public static void testExternal() throws IOException, UnsupportedEncodingException
	{
		String libraryName, resultName;

		console = new PrintStream(System.out, true, "UTF-8");
		try
		{
			output = new PrintStream("build/test/output-jar-external.txt", "UTF-8");
		}
		catch(IOException exception)
		{
			output = console;
		}

		output.println("testing jar external");
		output.println();
		output.flush();
		if(console != output)
			console.println("testing jar external");

		libraryName =   System.getProperty("user.dir")
		              + System.getProperty("file.separator")
		              + "build"
		              + System.getProperty("file.separator")
		              + "liblouisAPH-jni.so";
		LibLouisAPH.loadLibraryExternal(libraryName);
		setLogCallback();

		output.print("getExternalLibraryName    = ");
		output.flush();
		if(console != output)
		{
			console.print("getExternalLibraryName:  ");
			console.flush();
		}
		resultName = LibLouisAPH.getExternalLibraryName();
		output.println(libraryName);
		output.flush();
		if(!libraryName.equals(resultName))
		{
			output.println("ERROR:  getExternalLibraryName");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  getExternalLibraryName");
		}
		if(console != output)
		{
			console.println("PASS");
			console.flush();
		}

		doTests();
	}

	public static void testSystem() throws IOException, UnsupportedEncodingException
	{
		String libraryName;

		console = new PrintStream(System.out, true, "UTF-8");
		try
		{
			output = new PrintStream("build/test/output-jar-system.txt", "UTF-8");
		}
		catch(IOException exception)
		{
			output = console;
		}

		output.println("testing jar system");
		output.println();
		output.flush();
		if(console != output)
			console.println("testing jar system");

		//   -Djava.library.path=build
		LibLouisAPH.loadLibrarySystem("louisAPH-jni");
		setLogCallback();

		output.print("getSystemLibraryName      = ");
		output.flush();
		if(console != output)
		{
			console.print("getSystemLibraryName:  ");
			console.flush();
		}
		libraryName = LibLouisAPH.getSystemLibraryName();
		output.println(libraryName);
		output.flush();
		if(!libraryName.equals("louisAPH-jni"))
		{
			output.println("ERROR:  getSystemLibraryName");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  getSystemLibraryName");
		}
		if(console != output)
		{
			console.println("PASS");
			console.flush();
		}

		doTests();
	}

/******************************************************************************/

	public static void main(String args[]) throws IOException, UnsupportedEncodingException
	{
		if(args.length > 0)
		switch(args[0])
		{
		case "internal":  testInternal();  return;
		case "external":  testExternal();  return;
		case "system":    testSystem();    return;
		}

		System.err.println("ERROR:  neither internal, external, nor system specified");
	}

/******************************************************************************/

}
