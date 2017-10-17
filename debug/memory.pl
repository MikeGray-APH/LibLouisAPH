#!/usr/bin/perl

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
