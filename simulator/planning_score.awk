
BEGIN {
   line=1
   score=0
   pathind = 1
}

FNR==NR {
   a[NR]=$0
   if(line<=27) {
      mapref[28-line][0] = ""
      nmapref=split(a[line],mapref[28-line],"") 
   }
   if(line==28) {
      for (t=1; t<=NF; t++) {
         visited[$t] = 0
      }
   }
   else bestDist = $1
   line++

   next
}

{
    x=$1
    y=$2
    print "x",x,"y",y

    if (pathind==1) {
        if(x!=0 || y!=0) {
             print "Path does not start at 0 0"
             print "Planning score: " 0
             exit 1
        }
        visited[0]=1
    }
    else {
        movdirX = (x - prevX)/2
        movdirY = (y - prevY)/2
        if(mapref[prevY+movdirY+14][prevX+movdirX+28]!="X") {
             print "prevY",prevY, "prevX", prevX ,"movY", movdirY ,"movX", movdirX
             print "Error in path"
             print "Planning score: " 0
             exit 1
        }
        if(mapref[y+14][x+28] ~ /[0-9]/) {
            visited[mapref[y+14][x+28]+0] = 1
        }
    }


    prevX = x
    prevY = y

    pathind++

}

END {
#    print "map"
#    for(l=27;l>=1;l--) {
#       for (c=1; c<=55; c++) {
#           printf("%s",mapref[l][c]) 
#       }
#       print ""
#    }

     if(x!=0 || y!=0) {
           print "Path does not finish at 0 0"
           print "Planning score: " 0
           exit 1
     }

     nTargets=0
     nonVisitedTargets=0
     for (t in visited) {
         if (visited[t]!=1) {
            print "Target " t " not visited"
            nonVisitedTargets++
         }
         nTargets++
     }

     robDist = (pathind-2)*2
     if(robDist < bestDist) robDist=bestDist
     score = bestDist/robDist - nonVisitedTargets/nTargets
     print "Planning score: " score
}
