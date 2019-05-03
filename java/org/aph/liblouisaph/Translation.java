/*

   Copyright 2019 American Printing House for the Blind Inc.

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
 * Contains static methods for inferfacing with
 * the LibLouisAPH library.
 */
public class Translation
{
	/**
	 * Plain text used for forward translation or is the result of backward
	 * translation.
	 */
	public String chars;

	/**
	 * Braille text that is the result of forward translation or is used for
	 * backward translation.
	 */
	public String dots;

	/**
	 * Table names used for translation.
	 */
	public String tables;

	/**
	 * Conversion names used to conversions.
	 */
	public String conversion;

	/**
	 * Mapping from chars to dots.
	 */
	public int charsToDotsMap[];

	/**
	 * Mapping from dots to chars.
	 */
	public int dotsToCharsMap[];

	/**
	 * Cursor position in chars.
	 */
	public int cursorChars;

	/**
	 * Cursor position in dots.
	 */
	public int cursorDots;
}
