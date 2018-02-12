gpio.mode(light, gpio.OUTPUT)
gpio.write(light, gpio.LOW)

function getLight()
    i2c.start(i2c_id)
    i2c.address(i2c_id, slave_address, i2c.TRANSMITTER)
    i2c.write(i2c_id, read_light)
    i2c.stop(i2c_id)
    i2c.start(i2c_id)
    i2c.address(i2c_id, slave_address, i2c.RECEIVER)
    local c = i2c.read(i2c_id,1)
    i2c.stop(i2c_id)
    print("Light level: "..tostring(string.byte(c)).."/255")
    return string.byte(c)
end

function lightOn()
    gpio.write(light, gpio.HIGH)
end

function lightOff()
    gpio.write(light, gpio.LOW)
end
