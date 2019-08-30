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

define out_mask_char

	set $mask = (unsigned char)$arg0
	if $mask == 1
		printf "_"
	end
	if $mask == 2
		printf "-"
	end
	if $mask == 3
		printf "="
	end

end

define out_translate_and_rule

	printf "translate:\n"
	if translate > 0
		out_translate translate
	end
	printf "\n"

	printf "rule:\n"
	if rule > 0
		out_rule rule
	end
	printf "\n"
end

define out_translate_input

	set $translate = (struct translate*)$arg0

	set $len = $translate->input_len
	if $len > 125
		set $len = 125
	end

	if $translate->input > 0

		if $translate->input_to_output_map > 0
			printf "                    "
			set $i0 = 0
			while $i0 < $translate->chars_len
				printf "%x", $i0 % 16
				set $i0 = $i0 + 1
			end
			printf "\n"
		end

		printf "   org_chars      = "
		if $translate->chars > 0
			call debug_output_convert_private($translate->tables[$translate->table_crs], $translate->chars, $translate->chars_len)
		end
		printf "\n"

		if $translate->input_to_output_map > 0
			printf "                    "
			set $i0 = 0
			while $i0 < $translate->chars_len
				if $translate->input_to_output_map[$i0] == -1
					printf "_"
				else
					printf "%x", ($translate->input_to_output_map[$i0]) % 16
				end
				set $i0 = $i0 + 1
			end
			printf "\n"
		end

		printf "\n"

		if $translate->input_map > 0
			printf "                    "
			set $i0 = 0
			while $i0 < $len
				if $translate->input_mask[$i0] == 0
					printf "%x", $i0 % 16
				else
					out_mask_char $translate->input_mask[$i0]
				end
				set $i0 = $i0 + 1
			end
			printf "\n"
		end
		if $translate->input_map > 0
			printf "                    "
			set $i0 = 0
			while $i0 <= $len && $translate->input[$i0] != 0
				if $translate->input_map[$i0] == -1
					printf "_"
				else
					printf "%x", ($translate->input_map[$i0]) % 16
				end
				set $i0 = $i0 + 1
			end
			printf "\n"
		end

		printf "   input          = "
		if $len > 0
#			call debug_output_chomp($translate->input, $len)
			call debug_output_convert_private($translate->tables[$translate->table_crs], $translate->input, $len)
		end
		printf "\n"

		if $translate->input_crs < 125
			printf "                    "
			set $i0 = 1
			while $i0 <= $translate->input_crs
				printf " "
				set $i0 = $i0 + 1
			end
			printf "^\n"
		end

	else
		printf "   input          = NULL\n"
	end

end

define out_translate_output

	set $translate = (struct translate*)$arg0

	set $len = $translate->output_max
	if $len > 125
		set $len = 125
	end

	if $translate->output > 0

		if $translate->output_to_input_map > 0
			printf "                    "
			set $i0 = 0
			while $i0 <= $len && $translate->output[$i0] != 0
				if $translate->output_mask[$i0] == 0
					printf "%x", $i0 % 16
				else
					out_mask_char $translate->output_mask[$i0]
				end
				set $i0 = $i0 + 1
			end
			printf "\n"
		end

		printf "   output         = "
		if $len > 0
			#call debug_output_chomp($translate->output, $len)
			call debug_output_convert_private($translate->tables[$translate->table_crs], $translate->output, $len)
		end
		printf "\n"

		if $translate->output_len <= $len
			printf "                    "
			set $i0 = 1
			while $i0 <= $translate->output_len
				printf " "
				set $i0 = $i0 + 1
			end
			printf "^"
		end
		printf "\n"

		if $translate->output_to_input_map > 0
			printf "                    "
			set $i0 = 0
			while $i0 <= $len && $translate->output[$i0] != 0
				if $translate->output_to_input_map[$i0] == -1
					printf "_"
				else
					printf "%x", ($translate->output_to_input_map[$i0]) % 16
				end
				set $i0 = $i0 + 1
			end
			printf "\n"
		end

	else
		printf "   output         = NULL\n"
	end

end

define out_translate

	set $translate = (struct translate*)$arg0

	out_translate_input $translate

	printf "\n"

	out_translate_output $translate

	printf "\n"

	printf "   input_crs      = %d\n", $translate->input_crs
	printf "   input_len      = %d\n", $translate->input_len

	printf "\n"

	printf "   output_len     = %d\n", $translate->output_len
	printf "   output_max     = %d\n", $translate->output_max
	printf "   output_inc     = %d\n", $translate->output_inc

	printf "\n"

	printf "   cursor_pos     = %d\n", $translate->cursor_pos
	printf "   cursor_set     = %d\n", $translate->cursor_set

	printf "   maps_use       = %d\n", $translate->maps_use
	printf "   changed        = %d\n", $translate->changed

	printf "\n"

end

########################################

define out_translate_input_at

	set $translate = (struct translate*)$arg0
	set $other_at = (int)$arg1

	set $len = $translate->input_len
	if $len > 125
		set $len = 125
	end

	if $translate->input > 0

		if $translate->input_to_output_map > 0
			printf "                    "
			set $i0 = 0
			while $i0 < $translate->chars_len
				printf "%x", $i0 % 16
				set $i0 = $i0 + 1
			end
			printf "\n"
		end

		printf "   org_chars      = "
		if $translate->chars > 0
			call debug_output_convert_private($translate->tables[$translate->table_crs], $translate->chars, $translate->chars_len)
		end
		printf "\n"

		if $translate->input_to_output_map > 0
			printf "                    "
			set $i0 = 0
			while $i0 < $translate->chars_len
				if $translate->input_to_output_map[$i0] == -1
					printf "_"
				else
					printf "%x", ($translate->input_to_output_map[$i0]) % 16
				end
				set $i0 = $i0 + 1
			end
			printf "\n"
		end

		printf "\n"

		if $translate->input_map > 0
			printf "                    "
			set $i0 = 0
			while $i0 < $len
				if $translate->input_mask[$i0] == 0
					printf "%x", $i0 % 16
				else
					out_mask_char $translate->input_mask[$i0]
				end
				set $i0 = $i0 + 1
			end
			printf "\n"
		end
		if $translate->input_map > 0
			printf "                    "
			set $i0 = 0
			while $i0 <= $len && $translate->input[$i0] != 0
				if $translate->input_map[$i0] == -1
					printf "_"
				else
					printf "%x", ($translate->input_map[$i0]) % 16
				end
				set $i0 = $i0 + 1
			end
			printf "\n"
		end

		printf "   input          = "
		if $len > 0
			#call debug_output_chomp($translate->input, $len)
			call debug_output_convert_private($translate->tables[$translate->table_crs], $translate->input, $len)
		end
		printf "\n"

		if $translate->input_crs < 125
			printf "                    "
			set $i0 = 0
			while $i0 <= $translate->input_len
				if $i0 == $other_at
					printf "^"
				else
					printf " "
				end
				set $i0 = $i0 + 1
			end
			printf "\n"
		end

	else
		printf "   input          = NULL\n"
	end

end

define out_translate_input_and

	set $translate = (struct translate*)$arg0
	set $other_and = (int)$arg1

	set $len = $translate->input_len
	if $len > 125
		set $len = 125
	end

	if $translate->input > 0

		if $translate->input_to_output_map > 0
			printf "                    "
			set $i0 = 0
			while $i0 < $translate->chars_len
				printf "%x", $i0 % 16
				set $i0 = $i0 + 1
			end
			printf "\n"
		end

		printf "   org_chars      = "
		if $translate->chars > 0
			call debug_output_convert_private($translate->tables[$translate->table_crs], $translate->chars, $translate->chars_len)
		end
		printf "\n"

		if $translate->input_to_output_map > 0
			printf "                    "
			set $i0 = 0
			while $i0 < $translate->chars_len
				if $translate->input_to_output_map[$i0] == -1
					printf "_"
				else
					printf "%x", ($translate->input_to_output_map[$i0]) % 16
				end
				set $i0 = $i0 + 1
			end
			printf "\n"
		end

		printf "\n"

		if $translate->input_map > 0
			printf "                    "
			set $i0 = 0
			while $i0 < $len
				if $translate->input_mask[$i0] == 0
					printf "%x", $i0 % 16
				else
					out_mask_char $translate->input_mask[$i0]
				end
				set $i0 = $i0 + 1
			end
			printf "\n"
		end
		if $translate->input_map > 0
			printf "                    "
			set $i0 = 0
			while $i0 <= $len && $translate->input[$i0] != 0
				if $translate->input_map[$i0] == -1
					printf "_"
				else
					printf "%x", ($translate->input_map[$i0]) % 16
				end
				set $i0 = $i0 + 1
			end
			printf "\n"
		end

		printf "   input          = "
		if $len > 0
			#call debug_output_chomp($translate->input, $len)
			call debug_output_convert_private($translate->tables[$translate->table_crs], $translate->input, $len)
		end
		printf "\n"

		if $translate->input_crs < 125
			printf "                    "
			set $i0 = 0
			while $i0 <= $translate->input_len
				if $i0 == $translate->input_crs
					if $i0 == $other_and
						printf "\""
					else
						printf "^"
					end
				else
					if $i0 == $other_and
						printf "'"
					else
						printf " "
					end
				end
				set $i0 = $i0 + 1
			end
			printf "\n"
		end

	else
		printf "   input          = NULL\n"
	end

end

define out_translate_output_to

	set $translate = (struct translate*)$arg0
	set $other_to = (int)$arg1

	if $other_to > $translate->output_max
		set $len = $other_to
	else
		set $len = $translate->output_max
	end
	if $len > 125
		set $len = 125
	end

	if $translate->output > 0

		if $translate->output_to_input_map > 0
			printf "                    "
			set $i0 = 0
			while $i0 <= $len && $translate->output[$i0] != 0
				printf "%x", $i0 % 16
				set $i0 = $i0 + 1
			end
			printf "\n"
		end

		printf "   output         = "
		if $len > 0
			#call debug_output_chomp($translate->output, $len)
			call debug_output_convert_private($translate->tables[$translate->table_crs], $translate->output, $len)
		end
		printf "\n"

		if $translate->output_len <= $len
			printf "                    "
			set $i0 = 1
			while $i0 <= $translate->output_len
				printf " "
				set $i0 = $i0 + 1
			end
			printf "^"

			set $i0 = $i0 + 1
			if $other_to >= $i0
				while $i0 < $other_to
					printf " "
					set $i0 = $i0 + 1
				end
				printf "'"
			end
		end
		printf "  [%d %d]\n", $i0, $other_to

		if $translate->output_to_input_map > 0
			printf "                    "
			set $i0 = 0
			while $i0 <= $len && $translate->output[$i0] != 0
				if $translate->output_to_input_map[$i0] == -1
					printf "_"
				else
					printf "%x", ($translate->output_to_input_map[$i0]) % 16
				end
				set $i0 = $i0 + 1
			end
			printf "\n"
		end

	else
		printf "   output         = NULL\n"
	end

end

define out_translate_and

	set $translate = (struct translate*)$arg0
	set $input_at = (int)$arg1

	out_translate_input_and $translate $input_at

	printf "\n"

	out_translate_output $translate

	printf "\n"

	printf "   input_crs      = %d\n", $translate->input_crs
	printf "   input_len      = %d\n", $translate->input_len

	printf "\n"

	printf "   output_len     = %d\n", $translate->output_len
	printf "   output_max     = %d\n", $translate->output_max
	printf "   output_inc     = %d\n", $translate->output_inc

	printf "\n"

end

define out_translate_at_to

	set $translate = (struct translate*)$arg0
	set $input_at = (int)$arg1
	set $output_to = (int)$arg2

	out_translate_input_at $translate $input_at

	printf "\n"

	out_translate_output_to $translate $output_to

	printf "\n"

	printf "   input_crs      = %d\n", $translate->input_crs
	printf "   input_len      = %d\n", $translate->input_len

	printf "\n"

	printf "   output_len     = %d\n", $translate->output_len
	printf "   output_max     = %d\n", $translate->output_max
	printf "   output_inc     = %d\n", $translate->output_inc

	printf "\n"

end

define out_translate_and_to

	set $translate = (struct translate*)$arg0
	set $input_at = (int)$arg1
	set $output_to = (int)$arg2

	out_translate_input_and $translate $input_at

	printf "\n"

	out_translate_output_to $translate $output_to

	printf "\n"

	printf "   input_crs      = %d\n", $translate->input_crs
	printf "   input_len      = %d\n", $translate->input_len

	printf "\n"

	printf "   output_len     = %d\n", $translate->output_len
	printf "   output_max     = %d\n", $translate->output_max
	printf "   output_inc     = %d\n", $translate->output_inc

	printf "\n"

end

################################################################################

define out_translate_start

	printf "translate:\n"
	out_translate &translate_auto

	printf "\n"

	printf "direction  = "
	output direction
	printf "\n"

	printf "\n"

end

define n_translate_start
	next
	spacer
	out_translate_start
end

break translate_start
commands $bpnum

	call (void*)memset(&translate_auto, 0, sizeof(translate_auto))

	spacer
	out_translate_start

end
set $translate_start_bpnum = $bpnum
dis $translate_start_bpnum

################################################################################
