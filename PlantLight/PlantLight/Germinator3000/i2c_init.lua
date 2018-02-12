-- initialize i2c, set pin1 as sda, set pin2 as scl
i2c.setup(i2c_id, i2c_sda, i2c_scl, i2c.SLOW)

function i2c_test()
    i2c.start(i2c_id)
    i2c.address(i2c_id, slave_address, i2c.TRANSMITTER)
    i2c.write(i2c_id, comm_check)
    i2c.stop(i2c_id)
    i2c.start(i2c_id)
    i2c.address(i2c_id, slave_address, i2c.RECEIVER)
    local result = string.byte(i2c.read(i2c_id,1))
    i2c.stop(i2c_id)
    return result
end
