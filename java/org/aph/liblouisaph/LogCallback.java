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

/**
 * Handles log message callbacks.
 */
public interface LogCallback
{
	int LOG_ALL      = 1;
	int LOG_TRACE    = 2;
	int LOG_DEBUG    = 3;
	int LOG_INFO     = 4;
	int LOG_WARNING  = 5;
	int LOG_ERROR    = 6;
	int LOG_FATAL    = 7;

	/**
	 * Called when library logs any message.
	 *
	 * @param logLevel     message type
	 * @param logMessage   log message
	 */
	void logCallback(int logLevel, String logMessage);
}
