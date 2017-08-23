# LibLouisAPH Braille Translation and Back-Translation Library
#
# Copyright (C) 2017 American Printing House for the Blind, Inc.
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

define out_create_path_file_name

	printf "file_name[%2d]  = %s\n", file_name_len, file_name
	if paths > 0
		printf "paths[%2d]      = %s\n", paths_len, paths
	end
	printf "path[%4d]     = %s\n", path_max, path

	printf "\n"

	printf "len            = %d  %s\n", len, &paths[len]
	printf "i              = %d\n", i

	printf "\n"

end


define n_create_path_file_name
	next
	spacer
	out_create_path_file_name
end


break create_path_file_name
commands $bpnum

	set len = 0

	spacer
	out_create_path_file_name

end
set $create_path_file_name_bpnum = $bpnum
dis $create_path_file_name_bpnum

########################################

define out_lookup_table

	printf "table          = 0x%x", table
	if table > 0
		printf "  %s", table->file_name
	end
	printf "\n"
	printf "paths[%2d]      = ", paths_len
	if paths > 0
		printf "%s\n", paths
	end

	printf "\n"

	printf "path           = %s\n", path
	printf "len            = %d\n", len
	printf "file_name_len  = %d\n", file_name_len

	printf "\n"

end


define n_lookup_table
	next
	spacer
	out_lookup_table
end


break lookup_table
commands $bpnum

	set table = (void*)0
	set paths = (void*)0
	set path[0] = 0
	set paths_len = 0
	set len = 0
	set file_name_len = 0

	spacer
	out_lookup_table

end
set $lookup_table_bpnum = $bpnum
dis $lookup_table_bpnum

########################################

define out_lookup_tables

	if names > 0
		printf "names       = %s\n", names
		printf "names[off]  = %s\n", &names[off]
		printf "names[crs]  = %s\n", &names[crs]
	else
		printf "names       =\n"
		printf "names[off]  =\n"
		printf "names[crs]  =\n"
	end
	printf "names_len  = %d\n", names_len
	printf "table_cnt  = %d\n", *table_cnt
	printf "len        = %d\n", len
	printf "off        = %d\n", off
	printf "crs        = %d\n", crs
	printf "i          = %d\n", i

	printf "\n"

end


define n_lookup_tables
	next
	spacer
	out_lookup_tables
end


break lookup_tables
commands $bpnum

	set names = (void*)0
	set tables = (void*)0
	set *table_cnt = 0
	set len = 0
	set 'off' = 0
	set crs = 0

	spacer
	out_lookup_tables

end
set $lookup_tables_bpnum = $bpnum
dis $lookup_tables_bpnum

########################################

define out_lookup_open_file

	printf "file_name[%2d]   = %s\n", file_name_len, file_name
	printf "adjacent_name   = %s\n", adjacent_name
	printf "paths[%2d]       = ", paths_len
	if paths > 0
		printf "%s\n", paths
	else
		printf "NULL\n"
	end
	printf "path            = %s\n", path
	printf "len             = %d\n", len

	printf "\n"

end


define n_lookup_open_file
	next
	spacer
	out_lookup_open_file
end


break lookup_open_file
commands $bpnum

	set paths = (void*)0
	set path[0] = 0
	set paths_len = 0
	set len = 0
	set file_name_len = 0

	spacer
	out_lookup_open_file

end
set $lookup_open_file_bpnum = $bpnum
dis $lookup_open_file_bpnum

################################################################################
