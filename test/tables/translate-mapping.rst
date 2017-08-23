
mode capital     ⠯⠭⠭   ⠭⠭⠽   ⠯⠭   ⠭⠽   ⠯   3

set space               bit00
chars \s $space
rule trans \s      0

set letter      bit06
set upper_case  bit07
set lower_case  bit08
set join_case   0

macro uplo
chars $1$2 $letter
join $join_case $1 $2 $upper_case $lower_case
rule trans $2 $3
eom

@uplo A a ⠉
@uplo B b ⠒
@uplo C c ⠤

rule trans abc ⠿
