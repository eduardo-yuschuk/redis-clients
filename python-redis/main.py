from weakref import ref
import redis
from time import time
from time import ctime

r = redis.Redis(host='localhost', port=6379, db=0)

key = 'demo1'

r.set(key, '1')

refTime = time()
count = 0
while True:
    value = r.get(key)
    now = time()
    if int(now) != int(refTime):
        print(ctime(now), key, value, count)
        refTime = now
        count = 0
    count += 1