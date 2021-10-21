
BEGIN {
   FS=""
   line=1;
   score=0;
}

FNR==NR {
   a[NR]=$0

   next
}

{
     nmap=split($0,map,"") 
     nmapref=split(a[line],mapref,"") 

     if (length(map)!=55) {
         print "line length is not correct!"
     }

     for(i=1;i<=length(a[line]);i++) {
         if(map[i]!=" ") {
              if(mapref[i]==map[i]) {
                   score+=10  # correctly mapped
              }
              else score-=5   # uncorrectly mapped
         }
     }
     line++
}

END {
    if (line!=28) {
         print "number of lines is not correct!"
    }
    print "mapping score:" score
}
