#
#   Copyright 2017 American Printing House for the Blind Inc.
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#

################################################################################

define out_utf16le_convert_escapes

	printf "uchars      = "
	call debug_output_chomp(uchars, uchars_len)
	printf "\n"
	printf "uchars_len  = %d\n", uchars_len
	printf "\n"
	printf "crs  = %3d   ", crs
	call debug_output_uchar(uchars[crs], 0, 0)
	printf "\n"
	printf "off  = %3d   ", off
	call debug_output_uchar(uchars[off], 0, 0)
	printf "\n"
	printf "hex  = 0x%04x\n", hex
	printf "i    = %d\n", i
	printf "\n"
end

define n_utf16le_convert_escapes
	next
	spacer
	out_utf16le_convert_escapes
end

break utf16le_convert_escapes
commands $bpnum

	set crs = 0
	set off = 0
	set hex = 0

	spacer
	out_utf16le_convert_escapes

end
set $utf16le_convert_escapes_bpnum = $bpnum
dis $utf16le_convert_escapes_bpnum

################################################################################
