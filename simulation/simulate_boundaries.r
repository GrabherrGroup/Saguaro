args<-commandArgs(TRUE)
n<-args[1]
sample(c(args[2]:args[3]),n)->x
cumsum(x)->y
z<-sort(c(1,y,y))
write.table(file=args[4],z,quote=F,row.names=F,col.names=F)

