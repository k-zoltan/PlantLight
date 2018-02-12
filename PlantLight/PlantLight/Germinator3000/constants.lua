-- Pin for the light switch
light = 4
-- Fan switch pin... for later
fan = 5

-- I2C pins
i2c_id  = 0
i2c_sda = 1
i2c_scl = 2

-- I2C commands
slave_address = 0x40

comm_check = 0x10
read_light = 0xA0
read_temperature = 0xA1

--Other stuff
light_threshold = 200


