begin="0000000"
end="1000000"




length=7
while(True):
    print("sed -i \"s/constexpr size_t width="+
    str(length-1)+
    "/constexpr size_t width="+
    str(length)+
    "/g\" kaprekar.cpp; /usr/bin/clang++ -std=c++1z -o kaprekar kaprekar.cpp -O3; ./kaprekar "+
    begin+" "+
    end+"\n")
    length+=1
    begin="0"+begin
    end="0"+end

