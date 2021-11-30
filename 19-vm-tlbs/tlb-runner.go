package main

import (
	"fmt"
	"os"
	"os/exec"
	"strconv"
)

func main() {
	wd, _ := os.Getwd()
	pageCounts := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000}

	for _, i := range pageCounts {
		cmd := exec.Command(wd+"/tlb", strconv.Itoa(i))
		output, err := cmd.Output()
		if err != nil {
			fmt.Println("err", err)
		}
		fmt.Printf("%v: %v\n", i, string(output))
	}
}
