import DAN

ServerURL='ServerURL'# for secure connection
Comm_interval = 10 # unit:second

def profile_init():
    DAN.profile['dm_name']='PowerMeter'
    DAN.profile['d_name']='Meter.'+DAN.get_mac_addr()[-4:]

def odf():  # int only
    return []

def idf():
    return [
       ('Volt-I'   , float),
       ('Current-I', float),
       ('Power-I'  , float),
    ]
