This is ComputerNetwork Assignment2
OS: ubuntu
Socket Programming with C language

server ip_address : 192.168.0.45
client ip_address : 192.168.0.46
--- vim setting - ----


" 자동 문법 강조
syntax on

"color테마를 적용
":colorscheme spectro   "테마를 설치할 경우에 적용가능하다.

set nocompatible "Vi 와의 호환성을 없애고, Vim 만의 기능을 쓸 수 있게 함.
set hi=1000 "명령어 기록을 남길 갯수 지정
set bs=indent,eol,start "백스페이스 사용

"encoding setting
set enc=utf-8
set fenc=utf-8
set fencs=utf-8,cp949,cp932,euc-jp,shift-jis,big5,ucs-2le,latin1


set cindent "C언어 자동 들여쓰기 옵션
set autoindent " 자동 들여쓰기 옵션
set smartindent 

set tabstop=2    "탭에 대한 공백 크기 설정
set shiftwidth=2   "autoindent 옵션이 존재할때 후향 탭의 공백의 수를 정의
set nu      "라인 번호
set hls     "검색어 강조

"프로그램 시작시 플러그인 로드
set lpl

" 괄호 자동 완성 후 입력모드로 전환
map! () ()i
map! (); ();hi
map! [] []i
map! {} {}i
map! {}; {};iO
map! <> <>i
map! '' ''i
map! "" ""i

"vim plug-in on
filetype plugin on



출처: https://www.morenice.kr/5 [morenice's blog]
