--Load all the files needed for the Germinator 3000
dofile("constants.lua")
gpio.mode(light, gpio.OUTPUT)
gpio.write(light, gpio.LOW)
dofile("i2c_init.lua")
dofile("light.lua")

print("Germinator 3000 operational.\n")
