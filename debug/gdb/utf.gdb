# LibLouisAPH Braille Translation and Back-Translation Library
#
# Copyright (C) 2017 Mike Gray, American Printing House for the Blind, Inc.
#
# This file is part of LibLouisAPH.
#
# LibLouisAPH is free software: you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 2.1 of the License, or
# (at your option) any later version.
#
# LibLouisAPH is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with LibLouisAPH. If not, see <http://www.gnu.org/licenses/>.

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
