# Prints actual code for the GUI
# There are 16 buttons, this function writes code for each of them

# var status1: int = 0;
# in1.alpha = 0.3
# bn1.addEventListener(MouseEvent.CLICK, function1);
# function function1(event: MouseEvent){
#   if (changable){
#       if (status1 == 0){
#           status1 = 1;
#           in1.alpha = 1;
#       } else {
#           status1 = 0;
#           in1.alpha = 0.3;
#       }
#   }
# }

if __name__ == '__main__':
    for i in range(1, 17):
        print("var status"+str(i)+": int = 0;")
        print("in"+str(i)+".alpha = 0.3;")
        print("bn"+str(i)+".addEventListener(MouseEvent.CLICK, function" + str(i)+");")
        print("function function"+str(i)+"(event: MouseEvent){")
        print("  if (changable){")
        print("      if (status" + str(i)+ " == 0){")
        print("          status" + str(i)+ " = 1;")
        print("          in" + str(i)+ ".alpha = 1;")
        print("      } else {")
        print("          status" + str(i)+ " = 0;")
        print("          in" + str(i)+ ".alpha = 0.3;")
        print("      }")
        print("  }")
        print("}")
        print("")