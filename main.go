package main

import (
	"context"
	"fmt"
	"time"

	"github.com/go-redis/redis/v8"
)

func main() {

	fmt.Println("Starting...")
	ctx := context.Background()
	rdb := redis.NewClient(&redis.Options{
		Addr:     "localhost:6379",
		Password: "", // no password set
		DB:       0,  // use default DB
	})

	key := "demo1"

	err := rdb.Set(ctx, key, "1", 0).Err()
	if err != nil {
		panic(err)
	}

	refTime := time.Now()
	count := 0
	for {
		val, err := rdb.Get(ctx, key).Result()
		if err != nil {
			panic(err)
		}
		now := time.Now()
		if now.Second() != refTime.Second() {
			fmt.Println(time.Now(), key, val, count)
			refTime = now
			count = 0
		}
		count += 1
	}
}
