#!/usr/bin/perl

# LibLouisAPH Braille Translation and Back-Translation Library
#
# Copyright (C) 2017 American Printing House for the Blind, Inc. <www.aph.org>
#
# This file is part of LibLouisAPH.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

use strict;

my %allocs = ();

while(my $line = <STDIN>)
{
	chomp($line);
	if($line =~ /^([a-z]+)\s+([0-9a-f]+)/)
	{
		if($1 eq "alloc")
		{
			if(exists($allocs{$2}))
			{
				die "allocated:  $line\n";
			}
			$allocs{$2} = 0;
		}
		elsif($1 eq "free")
		{
			if(!exists($allocs{$2}))
			{
				die "not allocated:  $line\n";
			}
			delete($allocs{$2});
		}
	}
	else
	{
		die;
	}
}

print("remaining:\n");
for my $key (sort(keys(%allocs)))
{
	print("$key\n");
}

__END__
