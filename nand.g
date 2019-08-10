var i = 0
var NANDSize = 256
var nands : 256*3
var one = 1
var zero = 0
var a = 0
var b = 0
var c = 0

func GatherNANDs a b c 
  if i < NANDSize 
    i = i + one 
    nands : i = a 
    i = i + one 
    nands : i = b 
    i = i + one 
    nands : i = c 
  else  
    i = zero 
  end 
ret  
 

func main
  c = a !& b 
  GatherNANDs a b c 
ret
