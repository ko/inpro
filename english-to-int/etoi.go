/*
   The premise is that you're processing a checkbook. One 
   line has the words 
   
    > "thirty six thousand five hundred and sixty two"

    and the box next to it is empty--waiting for your output.
    The expected value, in this example, would be

    > 36562

    Make this happen.
*/

package main

import (
    "bufio"
    "fmt"
    "strings"
    "math"
)

var zeroes = make(map[string]int)
var etoi = make(map[string]int)

func init_zeroes() {
    zeroes["hundred"] = 2;
    zeroes["thousand"] = 3;
}

func init_etoi() {
    etoi["zero"] = 0;
    etoi["one"] = 1;
    etoi["two"] = 2;
    etoi["three"] = 3;
    etoi["four"] = 4;
    etoi["five"] = 5;
    etoi["six"] = 6;
    etoi["seven"] = 7;
    etoi["eight"] = 8;
    etoi["nine"] = 9;
    etoi["ten"] = 10;
    etoi["eleven"] = 11;
    etoi["twelve"] = 12;
    etoi["thirteen"] = 13;
    etoi["fourteen"] = 14;
    etoi["fifteen"] = 15;
    etoi["sixteen"] = 16;
    etoi["seventeen"] = 17;
    etoi["eighteen"] = 18;
    etoi["nineteen"] = 19;
    etoi["twenty"] = 20;
    etoi["thirty"] = 30;
    etoi["fourty"] = 40;
    etoi["fifty"] = 50;
    etoi["sixty"] = 60;
    etoi["seventy"] = 70;
    etoi["eight"] = 80;
    etoi["ninety"] = 90;
}

func main() {

    count := 0
    var token = ""
    var val = 0;
    var temp = 0;

    init_zeroes();
    init_etoi();

    const input = "thirty six thousand five hundred and sixty two"

    scanner := bufio.NewScanner(strings.NewReader(input))
    scanner.Split(bufio.ScanWords)

Scanning:
    for scanner.Scan() {
        token = scanner.Text()

        var i, ok = etoi[token]
        if (ok != false) {
            temp = temp + i
            continue Scanning
        }

        i , ok = zeroes[token]
        if (ok != false) {
            val = val + temp * int(math.Pow10(i))
            temp = 0
        }

        count++
    }

    if (temp > 0) {
        val += temp
    }

    fmt.Printf("%s is %d\n", input, val)

}
