#
#   Copyright 2018 American Printing House for the Blind Inc.
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

config process nemeth-ueb


#                  01234567890123456789012345678901
#                  0123456789ABCDEFGHIJKLMNOPQRSTUV
config attrs_chars _#a~=56789ABCDEFGHIJKLMNOPQRSTUV

set space   bit00
set digit   bit01
set letter  bit02
set script_thru  bit03
set comparator bit04


########################################
#   Spaces
########################################

chars \s\t\n\r\x00a0\x2000\x2001\x2002\x2003\x2004\x2005\x2006\x2007\x2008\x2009\x200a\x200b $space
chars \x2800 $space

#   spaces
rule trans \t       0
#ule trans \n       0
#ule trans \r       0
rule trans \x00a0   0
rule trans \x2000   0
rule trans \x2001   0
rule trans \x2002   0
rule trans \x2003   0
rule trans \x2004   0
rule trans \x2005   0
rule trans \x2006   0
rule trans \x2007   0
rule trans \x2008   0
rule trans \x2009   0
rule trans \x200a   0
rule trans \x200b   0
rule trans \s       0   # default back translation


########################################
#   Digits
########################################

chars 0123456789 $digit

rule trans 0 356
rule trans 1 2
rule trans 2 23
rule trans 3 25
rule trans 4 256
rule trans 5 26
rule trans 6 235
rule trans 7 2356
rule trans 8 236
rule trans 9 35


########################################
#   Letters
########################################

chars ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz $letter

rule trans a 1
rule trans b 12
rule trans c 14
rule trans d 145
rule trans e 15
rule trans f 124
rule trans g 1245
rule trans h 125
rule trans i 24
rule trans j 245
rule trans k 13
rule trans l 123
rule trans m 134
rule trans n 1345
rule trans o 135
rule trans p 1234
rule trans q 12345
rule trans r 1235
rule trans s 234
rule trans t 2345
rule trans u 136
rule trans v 1236
rule trans w 2456
rule trans x 1346
rule trans y 13456
rule trans z 1356

rule trans A 6-1
rule trans B 6-12
rule trans C 6-14
rule trans D 6-145
rule trans E 6-15
rule trans F 6-124
rule trans G 6-1245
rule trans H 6-125
rule trans I 6-24
rule trans J 6-245
rule trans K 6-13
rule trans L 6-123
rule trans M 6-134
rule trans N 6-1345
rule trans O 6-135
rule trans P 6-1234
rule trans Q 6-12345
rule trans R 6-1235
rule trans S 6-234
rule trans T 6-2345
rule trans U 6-136
rule trans V 6-1236
rule trans W 6-2456
rule trans X 6-1346
rule trans Y 6-13456
rule trans Z 6-1356


rule trans \x03b1 46-1 α
rule trans \x03b2 46-12 β
rule trans \x03b3 46-1245 γ
rule trans \x03b4 46-145 δ
rule trans \x03b5 46-15 ε
rule trans \x03b6 46-156 ζ
rule trans \x03b7 46-236 η
rule trans \x03b8 46-1456 θ
rule trans \x03b9 46-24 ι
rule trans \x03bA 46-13 κ
rule trans \x03bB 46-123 λ
rule trans \x03bC 46-134 μ
rule trans \x03bD 46-1345 ν
rule trans \x03bE 46-1346 ξ
rule trans \x03bF 46-135 ο
rule trans \x03c0 46-1234 π
rule trans \x03c1 46-1235 ρ
rule trans \x03c3 46-234 σ
rule trans \x03c4 46-2345 τ
rule trans \x03c5 46-136 υ
rule trans \x03c6 46-124 φ
rule trans \x03c7 46-12346 χ
rule trans \x03c8 46-125 ψ
rule trans \x03c9 46-135 ω

rule trans \x0391 46-6-1 Α
rule trans \x0392 46-6-12 Β
rule trans \x0393 46-6-1245 Γ
rule trans \x0394 46-6-145 Δ
rule trans \x0395 46-6-15 Ε
rule trans \x0396 46-6-156 Ζ
rule trans \x0397 46-6-236 Η
rule trans \x0398 46-6-1456 Θ
rule trans \x0399 46-6-24 Ι
rule trans \x039A 46-6-13 Κ
rule trans \x039B 46-6-123 Λ
rule trans \x039C 46-6-134 Μ
rule trans \x039D 46-6-1345 Ν
rule trans \x039E 46-6-1346 Ξ
rule trans \x039F 46-6-135 Ο
rule trans \x03a0 46-6-1234 Π
rule trans \x03a1 46-6-1235 Ρ
rule trans \x03a3 46-6-234 Σ
rule trans \x03a4 46-6-2345 Τ
rule trans \x03a5 46-6-136 Υ
rule trans \x03a6 46-6-124 Φ
rule trans \x03a7 46-6-12346 Χ
rule trans \x03a8 46-6-125 Ψ
rule trans \x03a9 46-6-135 Ω


########################################
#   Spacers
########################################

#   spacer
rule fini \I\I  \x2800
rule fini \I    \x2800
match fini ^ \I -   - - -
match fini - \I ^   - - -

macro script_thru
chars $1 $script_thru
rule trans $1 $2
match premode ^|!\s $1 !\s|^   - \I$1\I -
match premode - \s$1 !\s|^   - \I$1\I -
match premode ^|!\s $1\s -   - \I$1\I -
rule  premode \s$1\s   \I$1\I
rule postmode $1\I\I$1 $1$1
eom

@script_thru \x2012 36-36   # ‒
@script_thru \x2013 36-36   # –
@script_thru \x2014 36-36-36-36   # —
@script_thru \x2015 36-36-36-36   # ―
@script_thru \x2026 3-3-3   # …
rule init ... …


#⩦↞↟↠↡↢↣↨↩↪↫↬↯↶↷↺↻↥↧↨↹⇤⇥↾↿⇂⇃⥜⥝⥠⥡⇅⇈⇊⇶⤒⤓⤧⤨⤩⤪⤭⤮⤱⤲⥌⥍⥏⥑⥒⥓⥔⥕⥖⥗⥘⥙⥣⥥⥮⥯≆≲≳≴≵≶≷≸≹⊊⊋⪇⪈⪉⪊⪝⪞⪟⪠⪯⪰⪱⪲⪳⪴⪵⪶⪷⪸⪹⪺⫇⫈⫉⫊⫋⫌


rule init \x219a ⠌←   ↚
rule init \x219b ⠌→   ↛
rule init \x21ae ⠌↔   ↮
rule init \x21cd ⠌⇐   ⇍
rule init \x2209 ⠌∈   ∉
rule init \x220c ⠌∋   ∌
rule init \x2226 ⠌∥   ∦
rule init \x2244 ⠌≃   ≄
rule init \x2247 ⠌≅   ≇
rule init \x2249 ⠌≈   ≉
rule init \x2260 ⠌=   ≠
rule init \x2262 ⠌≡   ≢
rule init \x226e ⠌<   ≮
rule init \x226f ⠌>   ≯
rule init \x2270 ⠌≤   ≰
rule init \x2271 ⠌≥   ≱
rule init \x2280 ⠌≺   ⊀
rule init \x2281 ⠌≻   ⊁
rule init \x2284 ⠌⊂   ⊄
rule init \x2285 ⠌⊃   ⊅
rule init \x2288 ⠌⊆   ⊈
rule init \x2289 ⠌⊇   ⊉


macro comparator
chars $1 $comparator
rule trans $1 $2
match premode ^|!\s $1 !\s|^   - \I$1\I -
match premode - \s$1 !\s|^   - \I$1\I -
match premode ^|!\s $1\s -   - \I$1\I -
rule  premode \s$1\s   \I$1\I
match premode ^|!\s ⠌$1 !\s|^   - \I⠌$1\I -
match premode - \s⠌$1 !\s|^   - \I⠌$1\I -
match premode ^|!\s ⠌$1\s -   - \I⠌$1\I -
rule  premode \s⠌$1\s   \I⠌$1\I
eom

@comparator \x003c 5-13   # <
@comparator \x003d 46-13   # =
@comparator \x003e 46-2   # >
@comparator \x007e 4-156   # ~  can also not be a comparator
@comparator \x2208 4-15   # ∈
@comparator \x220b 4-26   # ∋
@comparator \x221d 456-123456   # ∝
@comparator \x2225 1246-123   # ∥
@comparator \x22bb 4-346-156   # ⊻
@comparator \x22bc 156-4-146   # ⊼
@comparator \x22bd 156-4-346   # ⊽
@comparator \x2236 5-2   # ∶
@comparator \x2237 56-23   # ∷
@comparator \x2242 156-4-156   # ≂
@comparator \x2243 4-156-156   # ≃
@comparator \x2245 4-156-46-13   # ≅
@comparator \x2248 4-156-4-156   # ≈
@comparator \x224a 4-156-4-156-156   # ≊
@comparator \x224b 4-156-4-156-4-156   # ≋?
@comparator \x224e 4-126-6-126   # ≎
@comparator \x2261 456-123   # ≡
@comparator \x2264 5-13-156   # ≤
@comparator \x2265 46-2-156   # ≥
@comparator \x2266 5-13-46-13   # ≦
@comparator \x2267 46-2-46-13   # ≧
@comparator \x227a 46-5-13   # ≺
@comparator \x227b 46-46-2   # ≻
@comparator \x2282 456-5-13   # ⊂
@comparator \x2283 456-46-2   # ⊃
@comparator \x2286 456-5-13-156   # ⊆
@comparator \x2287 456-46-2-156   # ⊇
@comparator \x22dc 156-5-13   # ⋜
@comparator \x22dd 156-46-2   # ⋝

@comparator \x2250 5-46-13-126-16-12456   # ≐
@comparator \x2251 5-46-13-146-16-126-16-12456   # ≑
@comparator \x2257 5-46-13-126-46-16-12456   # ≗
@comparator \x2259 5-46-13-126-456-126-12456   # ≙
@comparator \x225a 5-46-13-126-456-146-12456   # ≚
@comparator \x225c 5-46-13-126-1246-2345-12456   # ≜
@comparator \x225f 5-46-13-126-456-236-12456   # ≟

@comparator \x27c2 1246-1235   # ⟂
@comparator \x2a2a 5-156-146-16-12456   # ⨪

@comparator \x2a5e 46-13-4-146   # ⩞
@comparator \x2a5f 4-146-156   # ⩟
@comparator \x2a60 4-146-46-13   # ⩠
@comparator \x2a61 4-346-156   # ⩡
@comparator \x2a62 46-13-4-346   # ⩢
@comparator \x2a63 4-346-46-13   # ⩣
#comparator \x2a66 123456   # ⩦
@comparator \x2a6a 5-4-156-126-16-12456   # ⩪
@comparator \x2a70 4-156-4-156-46-13   # ⩰
@comparator \x2a73 46-13-4-156   # ⩳
@comparator \x2a77 5-46-13-146-16-16-126-16-16-12456   # ⩷
@comparator \x2a7d 5-13-156   # ⩽
@comparator \x2a7e 46-2-156   # ⩾
@comparator \x2a95 156-5-13   # ⪕
@comparator \x2a96 156-46-2   # ⪖
@comparator \x2a99 46-13-5-13   # ⪙
@comparator \x2a9a 46-13-46-2   # ⪚
@comparator \x2a9b 46-13-5-13   # ⪛
@comparator \x2a9c 46-13-46-2   # ⪜
@comparator \x2ac5 456-5-13-46-13  # ⫅
@comparator \x2ac6 456-46-2-46-13  # ⫆
@comparator \x2af9 5-13-46-13   # ⫹
@comparator \x2afa 46-2-46-13   # ⫺

@comparator \x2190 1246-246-25-25   # ←
@comparator \x2191 1246-126-25-25-135   # ↑
@comparator \x2192 1246-25-25-135   # →
@comparator \x2193 1246-146-25-25-135   # ↓
@comparator \x2194 1246-246-25-25-135   # ↔
@comparator \x2195 1246-126-246-25-25-135   # ↕
@comparator \x2196 1246-45-246-25-25   # ↖
@comparator \x2197 1246-45-25-25-135   # ↗
@comparator \x2198 1246-56-25-25-135   # ↘
@comparator \x2199 1246-56-246-25-25   # ↙

@comparator \x2190 1246-246-25-25   # ←
@comparator \x2192 1246-25-25-135   # →
@comparator \x2194 1246-246-25-25-135   # ↔
@comparator \x21d0 1246-246-2356-2456   # ⇐

@comparator \x21a4 1246-246-25-25-1256   # ↤
#comparator \x21a5 1246-126-1256-25-25-135   # ↥
@comparator \x21a6 1246-1256-25-25-135   # ↦
#comparator \x21a7 1246-146-1256-25-25-135   # ↧
#comparator \x21a8 1246-146-1256-25-25-135-1256   # ↨
#comparator \x21b9 123456   # ↹
#comparator \x21e4 123456   # ⇤
#comparator \x21e5 123456   # ⇥

@comparator \x21bc 1246-4-246-25-25   # ↼
@comparator \x21bd 1246-6-246-25-25   # ↽
#comparator \x21be 1246-126-25-25-6-135   # ↾
#comparator \x21bf 1246-126-25-25-4-135   # ↿
@comparator \x21c0 1246-25-25-4-135   # ⇀
@comparator \x21c1 1246-25-25-6-135   # ⇁
#comparator \x21c2 1246-146-6-246-25-25   # ⇂
#comparator \x21c3 1246-146-4-246-25-25   # ⇃

@comparator \x295a 1246-4-246-25-25-1256   # ⥚
@comparator \x295b 1246-1256-25-25-4-135   # ⥛
#comparator \x295c 1246-126-1256-25-25-6-135   # ⥜
#comparator \x295d 1246-146-6-246-25-25-1256   # ⥝
@comparator \x295e 1246-6-246-25-251256   # ⥞
@comparator \x295f 1246-1256-25-25-6-135   # ⥟
#comparator \x2960 1246-126-1256-25-25-4-135   # ⥠
#comparator \x2961 1246-146-4-246-25-25-1256   # ⥡

@comparator \x21c4 1246-25-25-135-1246-246-25-25   # ⇄
#comparator \x21c5 1246-126-25-25-135-1246-146-25-25-135   # ⇅
@comparator \x21c6 1246-246-25-25-1246-25-25-135   # ⇆
@comparator \x21c7 1246-246-25-25-1246-246-25-25   # ⇇
#comparator \x21c8 1246-126-25-25-135-1246-126-25-25-135   # ⇈
@comparator \x21c9 1246-25-25-135-1246-25-25-135   # ⇉
#comparator \x21ca 1246-146-25-25-135-1246-146-25-25-135   # ⇊
@comparator \x21cb 1246-4-246-25-25-1246-25-25-6-135   # ⇋
@comparator \x21cc 1246-25-25-4-135-1246-6-246-25-25   # ⇌

@comparator \x21d0 1246-246-2356-2456   # ⇐
@comparator \x21d1 1246-126-2356-2356-135   # ⇑
@comparator \x21d2 1246-2356-2356-135   # ⇒
@comparator \x21d3 1246-146-2356-2356-135   # ⇓
@comparator \x21d4 1246-246-2356-2356-135   # ⇔
@comparator \x21d5 1246-126-246-2356-2356-135   # ⇕
@comparator \x21d6 1246-45-246-2356-2456   # ⇖
@comparator \x21d7 1246-45-2356-2356-135   # ⇗
@comparator \x21d8 1246-56-2356-2356-135   # ⇘
@comparator \x21d9 1246-56-246-2356-2456   # ⇙

@comparator \x21e0 1246-246-25-0-25   # ⇠
@comparator \x21e1 1246-126-25-0-25-135   # ⇡
@comparator \x21e2 1246-25-0-25-135   # ⇢
@comparator \x21e3 1246-146-25-0-25-135   # ⇣

#comparator \x21f6 1246-25-25-135-1246-25-25-135-1246-25-25-135   # ⇶

@comparator \x27f5 1246-246-25-25-25   # ⟵
@comparator \x27f6 1246-25-25-25-135   # ⟶
@comparator \x27f7 1246-246-25-25-25-135   # ⟷
@comparator \x27f8 1246-246-2356-2356-2456   # ⟸
@comparator \x27f9 1246-2356-2356-2356-135   # ⟹
@comparator \x27fa 1246-246-2356-2356-2356-135   # ⟺

@comparator \x27fb 1246-246-25-25-25-1256   # ⟻
@comparator \x27fc 1246-1256-25-25-25-135   # ⟼
@comparator \x27fd 1246-246-2356-2356-2456   # ⟽
@comparator \x27fe 1246-2356-2356-2356-135   # ⟾
@comparator \x27ff 1246-35-25-26-135   # ⟿

@comparator \x2906 1246-246-2356-2456-1256   # ⤆
@comparator \x2907 1246-1256-2356-2356-135   # ⤇

@comparator \x290c 1246-246-25-0-25   # ⤌
@comparator \x290d 1246-25-0-25-135   # ⤍
@comparator \x290e 1246-246-25-0-25   # ⤎
@comparator \x290f 1246-25-0-25-135   # ⤏
@comparator \x2911 1246-2-2-2-135   # ⤑

#comparator \x2912 123456   # ⤒
#comparator \x2913 123456   # ⤓

@comparator \x2921 1246-56-246-25-25-135   # ⤡
@comparator \x2922 1246-45-246-25-25-135   # ⤢

#comparator \x2927 1246-45-246-25-25-1246-45-25-25-135   # ⤧
#comparator \x2928 1246-45-25-25-135-1246-56-25-25-135   # ⤨
#comparator \x2929 1246-56-25-25-135-1246-56-246-25-25   # ⤩
#comparator \x292a 1246-56-246-25-25-1246-45-246-25-25   # ⤪
#comparator \x292d 1246-56-25-25-135-1246-45-25-25-135   # ⤭
#comparator \x292e 1246-45-25-25-135-1246-56-25-25-135   # ⤮
#comparator \x2931 1246-45-25-25-135-1246-45-246-25-25   # ⤱
#comparator \x2932 1246-45-246-25-25-1246-45-25-25-135   # ⤲

@comparator \x2942 1246-25-25-135-1246-246-25   # ⥂
@comparator \x2943 1246-246-25-25-1246-25-135   # ⥃
@comparator \x2944 1246-25-135-1246-246-25-25   # ⥄

@comparator \x294a 1246-4-246-25-25-6-135   # ⥊
@comparator \x294b 1246-6-246-25-25-4-135   # ⥋
#comparator \x294c 1246-246-25-25-135   # ⥌
#comparator \x294d 1246-246-25-25-135   # ⥍
@comparator \x294e 1246-4-246-25-25-4-135   # ⥎
#comparator \x294f 1246-246-25-25-135   # ⥏
@comparator \x2950 1246-6-246-25-25-6-135   # ⥐
#comparator \x2951 1246-246-25-25-135   # ⥑

#comparator \x2952 123456   # ⥒
#comparator \x2953 123456   # ⥓
#comparator \x2954 123456   # ⥔
#comparator \x2955 123456   # ⥕
#comparator \x2956 123456   # ⥖
#comparator \x2957 123456   # ⥗
#comparator \x2958 123456   # ⥘
#comparator \x2959 123456   # ⥙

@comparator \x2962 1246-4-246-25-25-1246-6-246-25-25   # ⥢
#comparator \x2963 1246-126-25-25-4-135-1246-126-25-25-6-135   # ⥣
@comparator \x2964 1246-25-25-4-135-1246-25-25-6-135   # ⥤
#comparator \x2965 1246-146-4-246-25-25-1246-146-6-246-25-25   # ⥥
@comparator \x2966 1246-4-246-25-25-1246-25-25-4-135   # ⥦
@comparator \x2967 1246-6-246-25-25-1246-25-25-6-135   # ⥧
@comparator \x2968 1246-25-25-4-135-1246-4-246-25-25   # ⥨
@comparator \x2969 1246-25-25-6-135-1246-6-246-25-25   # ⥩
#comparator \x296e 1246-126-25-25-4-135-1246-146-6-246-25-25   # ⥮
#comparator \x296f 1246-146-4-246-25-25-1246-126-25-25-6-135   # ⥯

@comparator \x2971 46-13-1246-25-25-135   # ⥱
@comparator \x2972 4-156-1246-25-25-135   # ⥲
@comparator \x2973 1246-246-25-25-4-156   # ⥳
@comparator \x2974 1246-25-25-135-4-156   # ⥴
@comparator \x2975 1246-25-25-135-4-156-4-156   # ⥵
@comparator \x2976 5-13-1246-246-25-25   # ⥶
@comparator \x2978 46-2-1246-25-25-135   # ⥸
@comparator \x2979 456-5-13-1246-25-25-135   # ⥹
@comparator \x297b 456-46-2-1246-246-25-25   # ⥻


########################################
#   Symbols
########################################

#ule trans \x0021 235 !
rule trans \x0021 12346 !
rule trans \x0023 46-3456 #
rule trans \x0024 4-234 $
rule trans \x0025 4-356 %
rule trans \x0026 456-12346 &
rule trans \x0028 12356 (
rule trans \x0029 23456 )
rule trans \x002a 4-3456 *
rule trans \x002c 6 ,   decimal point
rule trans \x002b 346 +
rule trans \x002d 36 -
rule trans \x002e 6 .   decimal point
rule trans \x002f 456-34   /
rule trans \x003a 25 :
rule trans \x003b 23 ;
rule trans \x003f 236 ?
rule trans \x0040 4-1 @
rule trans \x005b 4-12356 [
rule trans \x005c 456-16 \
rule trans \x005d 4-23456 ]
rule trans \x005e 456-126 ^
rule trans \x007b 46-12356 {
rule trans \x007c 1256 |
rule trans \x007d 46-23456 }
rule trans \x00a7 4-6-234 §
rule trans \x00b0 46-16 °   degree (nemeth uses ring operator ∘)
rule trans \x00b1 346-36 ±   plus minus
rule trans \x00b6 4-6-1234 ¶
rule trans \x00b7 34 ·   dot operator
rule trans \x00c5 4-6-1 Å   angstrom unit
rule trans \x00d7 4-16 ×   multiplication cross
rule trans \x00f7 46-34 ÷   division sign

rule trans \x00a2 4-14 ¢

rule trans \x019b 4-46-123 ƛ

rule trans \x2010 36 ‐   hyphen
rule trans \x2011 36 ‑   non-breaking hyphen
rule trans \x2016 1256-1256 ‖   double vertical bar

rule trans \x2020 456-12456 †
rule trans \x2020 456-456-12456 ‡

rule trans \x2032 3 ′   prime
rule trans \x2033 3-3 ″   double primes
rule trans \x2034 3-3-3 ‴   triple primes
rule trans \x2057 3-3-3-3 ⁗   quad primes

rule trans \x2061 -   function application
rule trans \x2062 -   invisible times
rule trans \x2063 -   invisible separator
rule trans \x2064 -   invisible plus

rule trans \x211e 4-6-1235 ℞

rule trans \x2160 6-24 Ⅰ
rule trans \x2161 6-6-24-24 Ⅱ
rule trans \x2162 6-6-24-24-24 Ⅲ
rule trans \x2163 6-6-24-1236 Ⅳ
rule trans \x2164 6-1236 Ⅴ
rule trans \x2165 6-6-1236-24 Ⅵ
rule trans \x2166 6-6-1236-24-24 Ⅶ
rule trans \x2167 6-6-1236-24-24-24 Ⅷ
rule trans \x2168 6-6-24-1346 Ⅸ
rule trans \x2169 6-1346 Ⅹ
rule trans \x216a 6-6-1346-24 Ⅺ
rule trans \x216b 6-6-1346-24-24 Ⅻ
rule trans \x216c 6-123 Ⅼ
rule trans \x216d 6-14 Ⅽ
rule trans \x216e 6-145 Ⅾ
rule trans \x216f 6-134 Ⅿ

rule trans \x2170 24 ⅰ
rule trans \x2171 24-24 ⅱ
rule trans \x2172 24-24-24 ⅲ
rule trans \x2173 24-1236 ⅳ
rule trans \x2174 1236 ⅴ
rule trans \x2175 1236-24 ⅵ
rule trans \x2176 1236-24-24 ⅶ
rule trans \x2177 1236-24-24-24 ⅷ
rule trans \x2178 24-1346 ⅸ
rule trans \x2179 1346 ⅹ
rule trans \x217a 1346-24 ⅺ
rule trans \x217b 1346-24-24 ⅻ
rule trans \x217c 123 ⅼ
rule trans \x217d 14 ⅽ
rule trans \x217e 145 ⅾ
rule trans \x217f 134 ⅿ

rule trans \x2200 4-12346 ∀
rule trans \x2202 4-145 ∂
rule trans \x2203 4-123456 ∃
rule init  \x2204 ⠌∃   ∄
rule trans \x2205 456-356 ∅
rule trans \x2207 46-1246 ∇
rule trans \x2218 46-16 ∘   ring operator
rule trans \x221e 6-123456 ∞

rule trans \x2211 46-6-234 ∑
rule trans \x2212 36 −   minus sign
rule trans \x2213 36-346 ∓   minus plus
rule trans \x2223 1256 ∣
rule init  \x2224 ⠌∣   ∤
rule trans \x2227 4-146 ∧
rule trans \x2228 4-346 ∨
rule trans \x2229 46-146 ∩
rule trans \x222a 46-346 ∪
rule trans \x222b 2346 ∫
rule trans \x222c 2346-2346 ∬
rule trans \x222d 2346-2346-2346 ∭
rule trans \x222e 2346-4-1246-14-12456 ∮
rule trans \x2234 6-16 ∴
rule trans \x2235 4-34 ∵
rule trans \x2238 46-36 ∸   dot minus

rule trans \x22c5 16 ·   dot operator

rule trans \x2329 46-46-12356 〈   opening angled bracket
rule trans \x2329 46-46-23456 〉   closing angled bracket

rule trans \x2605 1246-234 ★
rule trans \x2606 1246-234 ☆

rule trans \x2713 4-345 ✓
rule trans \x2714 4-345 ✔

rule trans \x2a1b 126-2346 ⨛
rule trans \x2a1c 146-2346 ⨜

rule trans \x2e22 4-45-12356 ⸢
rule trans \x2e23 4-45-23456 ⸣
rule trans \x2e24 4-56-12356 ⸤
rule trans \x2e25 4-56-23456 ⸥

rule trans \x3003 6-3 〃

rule trans +- 346-5-36
rule trans -+ 36-5-346
rule trans -- 36-5-36

rule trans +− 346-5-36
rule trans −+ 36-5-346
rule trans −− 36-5-36


########################################
#   Indicators
########################################

#   general omission symbol
rule trans \x283f -   ⠿

rule init \xf32e -   math begin
rule init \xf32f -   math end

rule init \xf330 -   expression-begin
rule init \xf331 -   expression-separator
rule init \xf332 -   expression-end

rule init \x2061 -   function application
rule init \x2062 -   invisible times
rule init \x2063 -   invisible separator
rule init \x2064 -   invisible plus

#   scripts

#rule trans  ⠪   subsup-comma

#   fractions

rule trans \xf500 ⠹    fraction-begin
rule trans \xf501 ⠌    fraction-separator
rule trans \xf502 ⠸⠌   fraction-separator-bevelled
rule trans \xf503 ⠼    fraction-end
match pretrans - \xf500\I %~   - \xf500 -
match pretrans %~ \I\xf503  -   - \xf503 -

rule trans \xf50c ⠹    fraction-simple-begin
rule trans \xf50d ⠌    fraction-simple-separator
rule trans \xf50e ⠸⠌   fraction-simple-separator-bevelled
rule trans \xf50f ⠼    fraction-simple-end
match pretrans - \xf50c\I %~   - \xf50c -
match pretrans %~ \I\xf50f  -   - \xf50f -

rule trans \xf504 ⠸⠹   fraction-mixed-begin
rule trans \xf505 ⠌    fraction-mixed-separator
rule trans \xf506 ⠸⠌   fraction-mixed-separator-bevelled
rule trans \xf507 ⠸⠼   fraction-mixed-end
match pretrans - \xf504\I %~   - \xf504 -
match pretrans %~ \I\xf507  -   - \xf507 -

rule trans \xf508 ⠠⠹    fraction-complex-begin
rule trans \xf509 ⠠⠌    fraction-complex-separator
rule trans \xf50a ⠠⠸⠌   fraction-complex-separator-bevelled
rule trans \xf50b ⠠⠼    fraction-complex-end
match pretrans - \xf508\I %~   - \xf508 -
match pretrans %~ \I\xf50b  -   - \xf50b -

#   underscripts

rule trans \xf5a0 -
rule trans \xf5a1 -
rule trans \xf5a2 -

#   overscripts

rule trans \xf5a3 -
rule trans \xf5a4 -
rule trans \xf5a5 -

#   under/overscripts

rule trans \xf5a6 -
rule trans \xf5a7 -
rule trans \xf5a8 -

#   roots

rule trans \xf5b0 126
rule trans \xf5b1 345
rule trans \xf5b2 12456
rule trans \xf5b3 345
rule trans \xf5b4 12456

match pretrans %~ \I ⠨*\xf5b2   - - -
match pretrans %~ \I ⠨*\xf5b4   - - -

#   tables

rule init \xf600 -   table-begin
rule init \xf601 -   table-end
rule init \xf602 -   table-row-begin
rule init \xf603 -   table-row-end
rule init \xf604 -   table-cell-begin
rule init \xf605 -   table-cell-end

rule init \xf610 -   table-nemeth-round-open
rule init \xf611 -   table-nemeth-round-close
rule init \xf612 -   table-nemeth-square-open
rule init \xf613 -   table-nemeth-square-close
rule init \xf614 -   table-nemeth-curly-open
rule init \xf615 -   table-nemeth-curly-close
rule init \xf616 -   table-nemeth-angled-open
rule init \xf617 -   table-nemeth-angled-close
rule init \xf618 -   table-nemeth-bar

