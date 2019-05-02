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

package org.aph.liblouisaph;

import java.io.IOException;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;

public class Test
{
	static private PrintStream output, console;

/******************************************************************************/

	private static ArrayList<String> logs = new ArrayList<String>();

	private static void outputLogs()
	{
		for(String log : logs)
		{
			output.println(log);
		//	if(console != output)
		//		console.println(log);
		}
		logs = new ArrayList<String>();
	}

	private static void outputLogsError(String error)
	{
		outputLogs();
		output.println("ERROR:  " + error);
		output.close();
		if(console != output)
			console.println("FAIL");
		throw new Error(error);
	}

	private static void setLogCallback()
	{
		LogCallback logCallback = new LogCallback()
		{
			public void logCallback(int logLevel, String logMessage)
			{
				switch(logLevel)
				{
				case 0:  logs.add("unknown log level " + logLevel);  break;

				case LogCallback.LOG_ALL:      logs.add("ALL:  " + logMessage);      break;
				case LogCallback.LOG_TRACE:    logs.add("TRACE:  " + logMessage);    break;
				case LogCallback.LOG_DEBUG:    logs.add("DEBUG:  " + logMessage);    break;
				case LogCallback.LOG_INFO:     logs.add("INFO:  " + logMessage);     break;
				case LogCallback.LOG_WARNING:  logs.add("WARNING:  " + logMessage);  break;
				case LogCallback.LOG_ERROR:    logs.add("ERROR:  " + logMessage);    break;
				case LogCallback.LOG_FATAL:    logs.add("FATAL:  " + logMessage);    break;
				}

//				switch(logLevel)
//				{
//				case 0:
//					output.println();
//					output.flush();
//					return;
//
//				case LogCallback.LOG_ALL:      output.print("ALL:  ");      break;
//				case LogCallback.LOG_TRACE:    output.print("TRACE:  ");    break;
//				case LogCallback.LOG_DEBUG:    output.print("DEBUG:  ");    break;
//				case LogCallback.LOG_INFO:     output.print("INFO:  ");     break;
//				case LogCallback.LOG_WARNING:  output.print("WARNING:  ");  break;
//				case LogCallback.LOG_ERROR:    output.print("ERROR:  ");    break;
//				case LogCallback.LOG_FATAL:    output.print("FATAL:  ");    break;
//				}
//				output.println(logMessage);
//				output.flush();

//				switch(logLevel)
//				{
//				case 0:
//					output.println();
//					output.flush();
//					return;
//
//				case LogCallback.LOG_ALL:      console.print("ALL:  ");      break;
//				case LogCallback.LOG_TRACE:    console.print("TRACE:  ");    break;
//				case LogCallback.LOG_DEBUG:    console.print("DEBUG:  ");    break;
//				case LogCallback.LOG_INFO:     console.print("INFO:  ");     break;
//				case LogCallback.LOG_WARNING:  console.print("WARNING:  ");  break;
//				case LogCallback.LOG_ERROR:    console.print("ERROR:  ");    break;
//				case LogCallback.LOG_FATAL:    console.print("FATAL:  ");    break;
//				}
//				console.println(logMessage);
//				console.flush();
			}
		};
		LibLouisAPH.setLogCallback(logCallback);
	}

/******************************************************************************/

	private static void testGetPaths(String result, boolean doOutput)
	{
		output.print("getPaths            = ");
		output.flush();
		if(doOutput)
		if(console != output)
			console.print("getPaths:  ");

		String paths = LibLouisAPH.getPaths();

		/*   result should be null   */
		if(paths == null)
		if(result == null)
		{
			output.println();
			if(console != output)
				console.println("PASS");
			outputLogs();
			return;
		}
		else
		{
			output.println();
			outputLogsError("getPaths:  null != " + result);
		}
		else if(result == null)
		{
			output.println();
			outputLogsError("getPaths:  " + paths + " != null");
		}

		output.println(paths);
		output.flush();

		if(!paths.equals(result))
			outputLogsError("getPaths:  " + paths + " != " + result);

		if(console != output)
			console.println("PASS");
		outputLogs();
	}

	private static void testSetPaths(String paths)
	{
		output.println("setPaths           := " + paths);
		output.flush();
		if(console != output)
		{
			console.print("setPaths:  ");
			console.flush();
		}

		if(LibLouisAPH.setPaths(paths) == 0)
			outputLogsError("setPaths");

		testGetPaths(paths, false);
	}

	private static void testAddPaths(String paths, String result)
	{
		output.println("addPaths           := " + paths);
		output.flush();
		if(console != output)
		{
			console.print("addPaths:  ");
			console.flush();
		}

		if(LibLouisAPH.addPaths(paths) == 0)
			outputLogsError("addPaths");

		testGetPaths(result, false);
	}

/******************************************************************************/

	private static void testTranslation(String chars, String cells, String tables, String conversion, int charsToDots[], int dotsToChars[], int cursors[])
	{
		int inputToOutput[] = new int[0x100];
		int outputToInput[] = new int[0x100];
		int cursor[] = new int[1];

		String forward, backward;

		output.print  ("translateForward    = ");
		output.flush();
		if(console != output)
		{
			console.print("translateForward:  ");
			console.flush();
		}

		cursor[0] = cursors[0];
		forward = LibLouisAPH.translateForward(chars, 0x100, tables, conversion, inputToOutput, outputToInput, cursor);
		if(forward == null)
		{
			output.println();
			outputLogsError("translateForward:  null");
		}

		output.println(forward);
		output.flush();

		if(!forward.equals(cells))
			outputLogsError("translateForward:  != " + cells);

		for(int i = 0; i < charsToDots.length; i++)
		if(charsToDots[i] != inputToOutput[i])
			outputLogsError("translateForward:  charsToDots[" + i + "]  " + charsToDots[i] + " != " + inputToOutput[i]);

		for(int i = 0; i < dotsToChars.length; i++)
		if(dotsToChars[i] != outputToInput[i])
			outputLogsError("translateForward:  dotsToChars[" + i + "]  " + dotsToChars[i] + " != " + outputToInput[i]);

		if(cursor[0] != cursors[1])
			outputLogsError("translateForward:  cursor  " + cursor[0] + " != " + cursors[1]);

		if(console != output)
			console.println("PASS");
		outputLogs();


		output.print("translateBackward   = ");
		output.flush();
		if(console != output)
		{
			console.print("translateBackward:  ");
			console.flush();
		}

		cursor[0] = cursors[2];
		backward = LibLouisAPH.translateBackward(cells, 0x100, tables, conversion, inputToOutput, outputToInput, cursor);
		if(backward == null)
		{
			output.println();
			outputLogsError("translateBackward:  null");
		}

		output.println(backward);
		output.flush();

		if(!backward.equals(chars))
			outputLogsError("translateBackward:  != " + chars);

		for(int i = 0; i < dotsToChars.length; i++)
		if(dotsToChars[i] != inputToOutput[i])
			outputLogsError("translateBackward:  dotsToChars[" + i + "]  " + dotsToChars[i] + " != " + inputToOutput[i]);

		for(int i = 0; i < charsToDots.length; i++)
		if(charsToDots[i] != outputToInput[i])
			outputLogsError("translateBackward:  charsToDots[" + i + "]  " + charsToDots[i] + " != " + outputToInput[i]);

		if(cursor[0] != cursors[3])
			outputLogsError("translateBackward:  cursor  " + cursor[0] + " != " + cursors[3]);

		if(console != output)
			console.println("PASS");
		outputLogs();
	}

	private static void testConversion(String cells, String converted, String conversion)
	{
		String forward, backward;

		output.print("convertForward      = ");
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
			outputLogsError("convertForward:  null");
		}

		output.println(forward);
		output.flush();

		if(!forward.equals(converted))
			outputLogsError("convertForward:  != " +  converted);

		if(console != output)
			console.println("PASS");
		outputLogs();


		output.print("convertBackward     = ");
		output.flush();
		if(console != output)
		{
			console.print("convertBackward:  ");
			console.flush();
		}

		backward = LibLouisAPH.convertBackward(converted, conversion);
		if(backward == null)
		{
			output.println();
			outputLogsError("convertBackward:  null");
		}

		output.println(backward);
		output.flush();

		if(!backward.equals(cells))
			outputLogsError("convertBackward:  != " +  cells);

		if(console != output)
			console.println("PASS");
		outputLogs();
	}

/******************************************************************************/

	public static void main(String args[]) throws IOException, UnsupportedEncodingException
	{
		String string;

		console = new PrintStream(System.out, true, "UTF-8");
		try
		{
			output = new PrintStream("build/test/output-java.txt", "UTF-8");
		}
		catch(IOException exception)
		{
			output = console;
		}

		output.println("testing java");
		output.println();
		output.flush();
		if(console != output)
			console.println("testing java");

		//   -Djava.library.path=build
		LibLouisAPH.loadLibrarySystem("louisAPH-jni");

		setLogCallback();

		output.println("getVersion          = " + LibLouisAPH.getVersion());
		output.flush();

		testGetPaths(null, true);
		testSetPaths("tables");
		testAddPaths("test/tables", "tables:test/tables");
		testTranslation(
			"x xx xxx xx x",
			"\u2815\u282a\u2800\u2815\u282a\u2815\u282a\u2800\u2815\u2815\u282a\u282a\u2800\u2815\u282a\u2815\u282a\u2800\u2815\u282a",
			"link.rst",
			null,
			new int[]{0,2,3,5,7,8,8,8,12,13,15,17,18,},
			new int[]{0,0,1,2,2,3,3,4,5,5,5,5,8,9,9,10,10,11,12,12,},
			new int[]{7,8,8,5,});
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
}
