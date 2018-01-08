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

public class Test
{
	static private PrintStream output;

	public static void main(String args[]) throws IOException, UnsupportedEncodingException
	{
		String string;

		PrintStream console = new PrintStream(System.out, true, "UTF-8");
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


		output.println("getVersion         = " + LibLouisAPH.getVersion());
		output.flush();


		output.print("getPaths           = ");
		output.flush();
		if(console != output)
			console.print("getPaths:  ");
		string = LibLouisAPH.getPaths();
		if(string != null)
		{
			output.println("ERROR:  getPaths null");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  getPaths");
		}
		output.println();
		output.flush();
		if(console != output)
			console.println("PASS");


		output.println("setPaths          := tables");
		output.flush();
		if(console != output)
		{
			console.print("setPaths:  ");
			console.flush();
		}
		if(LibLouisAPH.setPaths("tables") == 0)
		{
			output.println("ERROR:  setPaths");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  setPaths");
		}
		string = LibLouisAPH.getPaths();
		if(string == null)
		{
			output.println("ERROR:  getPaths null");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  getPaths null");
		}
		output.println("getPaths           = " + string);
		output.flush();
		if(!string.equals("tables"))
		{
			output.println("ERROR:  getPaths \"tables\"");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  getPaths");
		}
		if(console != output)
			console.println("PASS");


		output.println("addPaths          := test/tables");
		output.flush();
		if(console != output)
		{
			console.print("addPaths:  ");
			console.flush();
		}
		if(LibLouisAPH.addPaths("test/tables") == 0)
		{
			output.println("ERROR:  addPaths");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  addPaths");
		}
		string = LibLouisAPH.getPaths();
		if(string == null)
		{
			output.println("ERROR:  getPaths null");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  getPaths");
		}
		output.println("getPaths           = " + string);
		output.flush();
		if(!string.equals("tables:test/tables"))
		{
			output.println("ERROR:  getPaths \"tables:test\tables\"");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  getPaths");
		}
		if(console != output)
			console.println("PASS");


		int transCharsMap[] = {0,2,3,5,7,8,8,8,12,13,15,17,18};
		int transDotsMap[] = {0,0,1,2,2,3,3,4,5,5,5,5,8,9,9,10,10,11,12,12};
		int charsToDotsMap[] = new int[0x100];
		int dotsToCharsMap[] = new int[0x100];
		int cursorMap[] = new int[1];


		output.print("translateForward   = ");
		output.flush();
		if(console != output)
		{
			console.print("translateForward:  ");
			console.flush();
		}
		cursorMap[0] = 7;
		String trans = LibLouisAPH.translateForward("x xx xxx xx x", 51, "link.rst", null, charsToDotsMap, dotsToCharsMap, cursorMap);
		if(trans == null)
		{
			output.println();
			output.println("ERROR:  translateForward null");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateForward");
		}
		output.println(trans);
		output.flush();
		if(!trans.equals("\u2815\u282a\u2800\u2815\u282a\u2815\u282a\u2800\u2815\u2815\u282a\u282a\u2800\u2815\u282a\u2815\u282a\u2800\u2815\u282a"))
		{
			output.println("ERROR:  translateForward translation");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateForward");
		}
		for(int i = 0; i < 13; i++)
		if(charsToDotsMap[i] != transCharsMap[i])
		{
			output.println("ERROR:  translateForward charsToDotsMap");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateForward");
		}
		for(int i = 0; i < 20; i++)
		if(dotsToCharsMap[i] != transDotsMap[i])
		{
			output.println("ERROR:  translateForward dotsToCharsMap");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateForward");
		}
		if(cursorMap[0] != 8)
		{
			output.println("ERROR:  translateForward cursor");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateForward");
		}
		if(console != output)
			console.println("PASS");


		output.print("translateBackward  = ");
		output.flush();
		if(console != output)
		{
			console.print("translateBackward:  ");
			console.flush();
		}
		cursorMap[0] = 8;
		string = LibLouisAPH.translateBackward(trans, 51, "link.rst", null, charsToDotsMap, dotsToCharsMap, cursorMap);
		if(string == null)
		{
			output.println();
			output.println("ERROR:  translateBackward null");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateBackward");
		}
		output.println(string);
		output.flush();
		if(!string.equals("x xx xxx xx x"))
		{
			output.println("ERROR:  translateBackward translation");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateBackward");
		}
		for(int i = 0; i < 20; i++)
		if(charsToDotsMap[i] != transDotsMap[i])
		{
			output.println("ERROR:  translateBackward charsToDotsMap");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateBackward");
		}
		for(int i = 0; i < 13; i++)
		if(dotsToCharsMap[i] != transCharsMap[i])
		{
			output.println("ERROR:  translateBackward dotsToCharsMap");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateBackward");
		}
		if(cursorMap[0] != 5)
		{
			output.println("ERROR:  translateBackward cursor");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  translateBackward");
		}
		if(console != output)
			console.println("PASS");


		output.print("convertForward     = ");
		output.flush();
		if(console != output)
		{
			console.print("convertForward:  ");
			console.flush();
		}
		string = LibLouisAPH.convertForward(trans, "link.cvt");
		if(string == null)
		{
			output.println();
			output.println("ERROR:  convertForward null");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  convertForward");
		}
		output.println(string);
		output.flush();
		if(!string.equals(">< ><>< >><< ><>< ><"))
		{
			output.println("ERROR:  convertForward conversion");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  convertForward");
		}
		if(console != output)
			console.println("PASS");


		output.print("convertBackward    = ");
		output.flush();
		if(console != output)
		{
			console.print("convertBackward:  ");
			console.flush();
		}
		string = LibLouisAPH.convertBackward(string, "link.cvt");
		if(string == null)
		{
			output.println();
			output.println("ERROR:  null");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  convertBackward null");
		}
		output.println(string);
		output.flush();
		if(!string.equals("\u2815\u282a\u2800\u2815\u282a\u2815\u282a\u2800\u2815\u2815\u282a\u282a\u2800\u2815\u282a\u2815\u282a\u2800\u2815\u282a"))
		{
			output.println("ERROR:  convertBackward conversion");
			output.close();
			if(console != output)
				console.println("FAIL");
			throw new Error("ERROR:  convertBackward");
		}
		if(console != output)
			console.println("PASS");


		if(console != output)
		{
			console.println();
			output.close();
		}
		else
			output.println();
	}
}
