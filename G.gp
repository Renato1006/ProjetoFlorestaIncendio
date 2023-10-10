set term gif animate 
set output "Malha_Floresta.gif"

ti=0

do for [i=0:*]{
	arq=sprintf('Malha%.0f.dat',i)
	set cbrange [0:3]
	set palette defined (0 "white", 1 "green", 2 "red", 3 "grey" )
	unset border
	unset xtics
	unset ytics
	unset colorbox
	set border
	temp=sprintf("Tempo=%d",ti)
	set title temp
	plot arq matrix with image
	ti=ti+1
}
