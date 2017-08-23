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

define out_expression

	set $expr = (struct expression*)$arg0
	printf "   type = "
	output (enum pattern_type)$expr->type
	printf "\n"
	printf "   prv  = 0x%x\n", $expr->prv
	printf "   nxt  = 0x%x ", $expr->nxt

	if $expr->type == PTN_CHARS || $expr->type == PTN_SUBPATTERN
		printf "   data = "
		call debug_output(&$expr->data[1], $expr->data[0] + 1)
#		set $i = 1
#		while $i < $expr->data[0] + 1
#			printf "%c", $expr->data[$i]
#			set $i = $i + 1
#		end
		printf "\n"
	end
	if $expr->type == PTN_ATTRIBUTES
		printf "   data = 0x%x ", $expr->data[0]
		output /t $expr->data[0]
		printf "\n"
		printf "          0x%x ", $expr->data[1]
		output /t $expr->data[1]
		printf "\n"
	end
	if $expr->type == PTN_GROUP || $expr->type == PTN_NOT
		printf "   data = %d\n", $expr->data[0]
	end
	if $expr->type == PTN_ZERO_MORE || $expr->type == PTN_ONE_MORE || $expr->type == PTN_ALTERNATE
		printf "   data = %d %d\n", $expr->data[0], $expr->data[1]
	end

end

################################################################################

define out_pattern_compile_expression

	printf "\n"

	printf "input       = "
	call debug_output_line(input, input_len)
	printf "input_len   = %d\n", input_len
	printf "*input_crs  = %d\n", *input_crs
	if *input_crs >= 0 && *input_crs < input_len
		printf "            = "
		call debug_output_line(&input[*input_crs], input_len - *input_crs)
	end
	printf "input_end   = %d\n", input_end
	if input_end >= 0 && input_end < 27720
		printf "              = %s\n", &input[input_end]
	end

	printf "\n"

	printf "expr_data   = "
	output /d *expr_data@31
	printf "\n"
	printf "expr_len    = %d\n", expr_len

	printf "\n"

	printf "expr_start  = %d  ", expr_start
	if expr_start >= 2 && expr_start < 27720
		output expr_data[expr_start]@31
		printf "\n"
		out_expression &expr_data[expr_start]
	end

	printf "expr_end    = %d  ", expr_end
	if expr_end > 1 && expr_end < 27720
		output expr_data[expr_end]@31
		printf "\n"
		out_expression &expr_data[expr_end]
	end

	printf "expr_sub    = %d  ", expr_sub
	if expr_sub > 1 && expr_sub < 27720
		output expr_data[expr_sub]@31
		printf "\n"
		out_expression &expr_data[expr_sub]
	end

	printf "*expr_crs   = %d  ", *expr_crs
	if *expr_crs >= 0 && *expr_crs < 27720
		output expr_data[*expr_crs]@31
		printf "\n"
		out_expression &expr_data[*expr_crs]
	end

	printf "\n"

	printf "esc         = %d\n", esc
	printf "nest        = %d\n", nest
	printf "attrs0      = %x ", attrs0
	output /t attrs0
	printf "\n"
	printf "attrs1      = %x ", attrs1
	output /t attrs1
	printf "\n"
	printf "i           = %d\n", i

	printf "\n"

end

define n_pattern_compile_expression
	spacer
	next
	out_pattern_compile_expression
end

break pattern_compile_expression
commands $bpnum

	spacer
	out_pattern_compile_expression

end
set $pattern_compile_expression_bpnum = $bpnum
dis $pattern_compile_expression_bpnum

########################################

define out_pattern_compile_1

	printf "\n"

	printf "input         = "
	call debug_output_line(input, input_len)
	printf "input_len     = %d\n", input_len
	printf "*input_crs    = %d\n", *input_crs
	if *input_crs >= 0 && *input_crs < input_len
		printf "              = "
		call debug_output_line(&input[*input_crs], input_len - *input_crs)
	end

	printf "\n"

	printf "expr_data     = "
	output /d *expr_data@31
	printf "\n"
	printf "expr_len      = %d\n", expr_len

	printf "expr_crs_prv  = %d  ", expr_crs_prv
	if expr_crs_prv > 1 && expr_crs_prv < 27720
		output expr_data[expr_crs_prv]@31
		printf "\n"
		out_expression &expr_data[expr_crs_prv]
	end

	printf "*expr_crs     = %d  ", *expr_crs
	if *expr_crs >= 0 && *expr_crs < 27720
		output expr_data[*expr_crs]@31
		printf "\n"
		out_expression &expr_data[*expr_crs]
	end

	printf "\n"

end

define n_pattern_compile_1
	spacer
	next
	out_pattern_compile_1
end

break pattern_compile_1
commands $bpnum

	spacer
	out_pattern_compile_1

end
set $pattern_compile_1_bpnum = $bpnum
dis $pattern_compile_1_bpnum

########################################

define out_pattern_compile_2

	printf "\n"

	printf "expr_data   = "
	output /d *expr_data@31
	printf "\n"
	printf "expr_len    = %d\n", expr_len

	printf "\n"

	printf "expr_at     = %d  ", expr_at
	if expr_at > 1 && expr_at < 27720
		output expr_data[expr_at]@31
		printf "\n"
		out_expression &expr_data[expr_at]
	end

	printf "expr_start  = %d  ", expr_start
	if expr_start > 1 && expr_start < 27720
		output expr_data[expr_start]@31
		printf "\n"
		out_expression &expr_data[expr_start]
	end

	printf "expr_end    = %d  ", expr_end
	if expr_end > 1 && expr_end < 27720
		output expr_data[expr_end]@31
		printf "\n"
		out_expression &expr_data[expr_end]
	end

	printf "expr_prv    = %d  ", expr_prv
	if expr_prv > 1 && expr_prv < 27720
		output expr_data[expr_prv]@31
		printf "\n"
		out_expression &expr_data[expr_prv]
	end

	printf "expr_sub    = %d  ", expr_sub
	if expr_sub > 1 && expr_sub < 27720
		output expr_data[expr_sub]@31
		printf "\n"
		out_expression &expr_data[expr_sub]
	end

	printf "*expr_crs    = %d  ", *expr_crs
	if *expr_crs >= 0 && *expr_crs < 27720
		output expr_data[*expr_crs]@31
		printf "\n"
		out_expression &expr_data[*expr_crs]
	end
	printf "\n"

	printf "\n"

end

define n_pattern_compile_2
	spacer
	next
	out_pattern_compile_2
end

break pattern_compile_2
commands $bpnum

	spacer
	out_pattern_compile_2

end
set $pattern_compile_2_bpnum = $bpnum
dis $pattern_compile_2_bpnum

########################################

define out_pattern_compile_3

	printf "\n"

	printf "expr_data       = "
	output /d *expr_data@31
	printf "\n"
	printf "expr_len        = %d\n", expr_len

	printf "expr_at         = %d  ", expr_at
	if expr_at > 1 && expr_at < 27720
		output expr_data[expr_at]@31
		printf "\n"
		out_expression &expr_data[expr_at]
	end

	printf "*expr_crs       = %d  ", *expr_crs
	if *expr_crs >= 0 && *expr_crs < 27720
		output expr_data[*expr_crs]@31
		printf "\n"
		out_expression &expr_data[*expr_crs]
	end

	printf "expr_mrk        = %d  ", expr_mrk
	if expr_mrk > 1 && expr_mrk < 27720
		output expr_data[expr_mrk]@31
		printf "\n"
		out_expression &expr_data[expr_mrk]
	end

	printf "\n"

	printf "expr_start     = %d  ", expr_start
	if expr_start > 1 && expr_start < 27720
		output expr_data[expr_start]@31
		printf "\n"
		out_expression &expr_data[expr_start]
	end

	printf "expr_end        = %d  ", expr_end
	if expr_end > 1 && expr_end < 27720
		output expr_data[expr_end]@31
		printf "\n"
		out_expression &expr_data[expr_end]
	end

	printf "expr_sub_start  = %d  ", expr_sub_start
	if expr_sub_start > 1 && expr_sub_start < 27720
		output expr_data[expr_sub_start]@31
		printf "\n"
		out_expression &expr_data[expr_sub_start]
	end

	printf "expr_sub_end    = %d  ", expr_sub_end
	if expr_sub_end > 1 && expr_sub_end < 27720
		output expr_data[expr_sub_end]@31
		printf "\n"
		out_expression &expr_data[expr_sub_end]
	end
	printf "\n"

	printf "\n"

end

define n_pattern_compile_3
	spacer
	next
	out_pattern_compile_3
end

break pattern_compile_3
commands $bpnum

	spacer
	out_pattern_compile_3

end
set $pattern_compile_3_bpnum = $bpnum
dis $pattern_compile_3_bpnum

########################################

define out_pattern_compile

	printf "\n"

	printf "input         = "
	call debug_output_line(input, input_len)
	printf "input_len     = %d\n", input_len

	printf "input_crs     = %d\n", input_crs
	if input_crs >= 0 && input_crs < input_len
		printf "              = "
		call debug_output_line(&input[input_crs], input_len - input_crs)
	end

	printf "\n"

	printf "expr_data     = "
	output /d *expr_data@31
	printf "\n"
	printf "expr_len      = %d\n", expr_len
	printf "expr_data[0]  = %d\n", expr_data[0]
	printf "expr_data[1]  = %d\n", expr_data[1]

	printf "\n"

end

define n_pattern_compile
	spacer
	next
	out_pattern_compile
end

break pattern_compile
commands $bpnum

	spacer
	out_pattern_compile

end
set $pattern_compile_bpnum = $bpnum
dis $pattern_compile_bpnum

########################################

define out_pattern_reverse_expression

	printf "expr_data   = "
	output /x *expr_data@31
	printf "\n"

	printf "\n"

	printf "expr_start  = %d  ", expr_start
	if expr_start > 1 && expr_start < 27720
		output /x expr_data[expr_start]@31
		printf "\n"
		out_expression &expr_data[expr_start]
	end
	printf "\n"

	printf "expr_end    = %d  ", expr_end
	if expr_end > 1 && expr_end < 27720
		output /x expr_data[expr_end]@31
		printf "\n"
		out_expression &expr_data[expr_end]
	end
	printf "\n"

	printf "expr_prv    = %d  ", expr_prv
	if expr_prv > 1 && expr_prv < 27720
		output /x expr_data[expr_prv]@31
		printf "\n"
		out_expression &expr_data[expr_prv]
	end
	printf "\n"

	printf "expr_crs    = %d  ", expr_crs
	if expr_crs > 1 && expr_crs < 27720
		output /x expr_data[expr_crs]@31
		printf "\n"
		out_expression &expr_data[expr_crs]
	end
	printf "\n"

	printf "\n"

end

define n_pattern_reverse_expression
	spacer
	next
	out_pattern_reverse_expression
end

break pattern_reverse_expression
commands $bpnum

	spacer
	out_pattern_reverse_expression

end
set $pattern_reverse_expression_bpnum = $bpnum
dis $pattern_reverse_expression_bpnum

########################################

define out_pattern_check_expression

	printf "\n"

	printf "input             = "
	call debug_output_line(input, 0x1000)
	if *input_crs < 0
		printf "*input_crs        =^\n"
	else
		printf "*input_crs        = "
		set $i0 = *input_crs
		while $i0 >= 0
			printf " "
			set $i0 = $i0 - 1
		end
		printf "^\n"
	end

	printf "input_minmax      = %d\n", input_minmax
	printf "input_dir         = %d\n", input_dir

#	printf "input_start[%3d]  = ", input_start
#	if input_start >= 0 && (input_start * input_dir < input_minmax * input_dir)
#		printf "%s", &input[input_start]
#	end
#	printf "\n"
	if input_start >= 0
		printf "input_start[%3d]  = ", input_start
		if input_dir < 0
			call debug_output_line(input, input_start + 1)
		else
			call debug_output_line(&input[input_start], (input_minmax - input_start) + 1)
		end
	else
		printf "input_start       =\n"
	end

	printf "input_crs_prv     = %d\n", input_crs_prv

	printf "\n"

	printf "expr_data         = "
	call debug_pattern_print(expr_data, attrs_chars)
	printf "\n"
#	printf "                  = "
#	output /x *expr_data@13
#	printf "\n"

	if loop_crs > 1 && loop_crs < 27720
		printf "loop_crs[%4d]    = ", loop_crs
		call debug_pattern_print_expression(expr_data, loop_crs)
		printf "\n"
#		printf "                  = "
#		output /x expr_data[loop_crs]@13
#		printf "\n"
#		out_expression &expr_data[loop_crs]
	else
		printf "loop_crs          =\n"
	end

	if expr_crs > 1 && expr_crs < 27720
		printf "expr_crs[%4d]    = ", expr_crs
		call debug_pattern_print_expression(expr_data, expr_crs)
		printf "\n"
#		printf "                  = "
#		output /x expr_data[expr_crs]@13
#		printf "\n"
#		out_expression &expr_data[expr_crs]
	else
		printf "expr_crs          =\n"
	end

	printf "\n"

	printf "ret               = %d\n", ret
	printf "not               = %d\n", not
	printf "\n"

end

define n_pattern_check_expression
	spacer
	next
	out_pattern_check_expression
end

break pattern_check_expression
commands $bpnum

	set input_crs_prv = 0
	set input_start = 0
	set ret = 0
	set 'data' = (void*)0

	spacer
	out_pattern_check_expression

	printf "next = npce\n\n"

end
set $pattern_check_expression_bpnum = $bpnum
dis $pattern_check_expression_bpnum

define npce
n_pattern_check_expression
end

################################################################################
