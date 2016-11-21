BEGIN {
	prev = 0;
}
{
	diff = $2 - prev
	if (diff != 1 ) {
		print "Error! prev=" , prev, " cur=", $2 , " diff=", diff
	}
	prev = $2
}
