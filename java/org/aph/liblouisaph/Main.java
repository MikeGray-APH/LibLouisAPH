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

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;

public class Main
{
	private static PrintStream consoleOut, consoleErr;

	private static void printUsage()
	{
		String usage[] =
		{
			"Usage: [OPTIONS] TABLE_LIST [CONVERSION]",
			"Options:",
			"   -b          do back translation",
			"   -p PATHS    use external table paths PATHS",
			"   -l LIBRARY  use external library LIBRARY",
			"   -s LIBRARY  use system library LIBRARY",
			"   -v          print version",
			"   -h          print this message",
		};

		for(int i = 0; i < usage.length; i++)
			System.out.println(usage[i]);
	}

	private static void printVersion()
	{
		String version[] =
		{
			"Version:  " + Main.class.getPackage().getImplementationVersion(),
			"Copyright (C) 2017 American Printing House for the Blind, Inc. <www.aph.org>",
			"Licensed under the Apache License, Version 2.0 <http://www.apache.org/licenses/LICENSE-2.0>.",
		};

		for(int i = 0; i < version.length; i++)
			System.out.println(version[i]);
	}

	public static void main(String args[]) throws IOException, UnsupportedEncodingException
	{
		if(args.length < 1)
		{
			printUsage();
			return;
		}

		BufferedReader consoleIn = new BufferedReader(new InputStreamReader(System.in));
		consoleOut = new PrintStream(System.out, true, "UTF-8");
		consoleErr = new PrintStream(System.out, true, "UTF-8");

		String systemLibraryName    = null;
		String externalLibraryName  = null;
		String tablePaths           = null;
		int direction               = 1;

		int argn;
		for(argn = 0; argn < args.length; argn++)
		if(args[argn].charAt(0) == '-')
		switch(args[argn])
		{
		case "-b":  direction = -1;

		case "-p":

			argn++;
			if(argn < args.length)
				tablePaths = args[argn];
			break;

		case "-l":

			argn++;
			if(argn < args.length)
				externalLibraryName = args[argn];
			break;

		case "-s":

			argn++;
			if(argn < args.length)
				systemLibraryName = args[argn];
			break;

		case "-v":  printVersion();  return;
		case "-h":  printUsage();    return;
		}
		else
			break;

		if(argn == args.length)
			return;

		String tableList = args[argn++];
		String conversion = null;
		if(argn < args.length)
			conversion = args[argn];

		if(systemLibraryName != null)
			LibLouisAPH.loadLibrarySystem(systemLibraryName);
		else if(externalLibraryName != null)
			LibLouisAPH.loadLibraryExternal(externalLibraryName);
		else
			LibLouisAPH.loadLibraryInternal();

		LibLouisAPH.setLogCallback(new MainLogCallback(consoleOut, consoleErr));

		if(tablePaths == null)
			LibLouisAPH.setInternalTablePath();
		else
			LibLouisAPH.setPaths(tablePaths);

		String input, translation;
		while((input = consoleIn.readLine()) != null)
		{
			int length = input.length() * 5;
			if(length < 100)
				length = 100;
			if(direction > 0)
				translation = LibLouisAPH.translateForward(input, length, tableList, conversion, null, null, null);
			else
				translation = LibLouisAPH.translateBackward(input, length, tableList, conversion, null, null, null);
			if(translation != null)
				consoleOut.println(translation);
			else
				break;
		}
	}
}

class MainLogCallback implements LogCallback
{
	private PrintStream consoleOut, consoleErr;

	MainLogCallback(PrintStream consoleOut, PrintStream consoleErr)
	{
		this.consoleOut = consoleOut;
		this.consoleErr = consoleErr;
	}

	@Override
	public void logCallback(int logLevel, String logMessage)
	{
		consoleOut.flush();
		switch(logLevel)
		{
		case LogCallback.LOG_ALL:      consoleErr.print("ALL:  ");      break;
		case LogCallback.LOG_TRACE:    consoleErr.print("TRACE:  ");    break;
		case LogCallback.LOG_DEBUG:    consoleErr.print("DEBUG:  ");    break;
		case LogCallback.LOG_INFO:     consoleErr.print("INFO:  ");     break;
		case LogCallback.LOG_WARNING:  consoleErr.print("WARNING:  ");  break;
		case LogCallback.LOG_ERROR:    consoleErr.print("ERROR:  ");    break;
		case LogCallback.LOG_FATAL:    consoleErr.print("FATAL:  ");    break;
		}
		consoleErr.println(logMessage);
		consoleErr.flush();
	}
}
