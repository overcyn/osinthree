package main

import (
	"fmt"
	"strconv"
)

func BinToDec(bin string) (string, error) {
	ui, err := strconv.ParseUint(bin, 2, 64)
	if err != nil {
		return "", err
	}
	return fmt.Sprintf("%d", ui), nil
}

func HexToBin(hex string) (string, error) {
	ui, err := strconv.ParseUint(hex, 16, 64)
	if err != nil {
		return "", err
	}

	format := fmt.Sprintf("%%0%db", len(hex)*4)
	return fmt.Sprintf(format, ui), nil
}

func main() {
	bin, _ := HexToBin("00001986")
	fmt.Println(bin)

	// get after 10 digits
	vpn, _ := strconv.ParseUint(bin[:22], 2, 64)
	offset, _ := strconv.ParseUint(bin[22:], 2, 64)
	fmt.Println(vpn, offset)

	table := []string{"0000018", "0000000", "0000000", "000000c", "0000009", "0000000", "000001d", "0000013", "0000000", "000001f", "000001c", "0000000", "000000f", "0000000", "0000000", "0000008"}
	valid := []int{8, 0, 0, 8, 8, 0, 8, 8, 0, 8, 8, 0, 8, 0, 0, 8}

	pfn, _ := strconv.ParseUint(table[vpn], 16, 64)
	fmt.Println(valid[vpn], pfn<<10+offset)
}
