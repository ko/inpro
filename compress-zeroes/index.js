/*
 * Output:
 *
 *      $ node index.js 
 *      input:
 *      [ 0, 1, 1, 0, 4, 3, 2, 0, 3 ]
 *      encoded:
 *      [ 118, [ 1, 1, 4, 3, 2 ], 1, [ 3 ] ]
 *      decoded:
 *      [ 0, 1, 1, 0, 4, 3, 2, 0, 3, 0, 0, 0, 0, 0, 0, 0 ]
 *
 */

const MASK_LENGTH = 8;
const input = [0,1,1,0,4,3,2,0,3];
const encoded = [];
const decoded = [];

console.log('input:');
console.log(input);

for (let i = 0; i < input.length; i += MASK_LENGTH) {
    let tmp = encoded;
    let mask = 0;
    let intermediate = [];
    for (let j = 0; j < MASK_LENGTH; j++) {
        if ((i + j) >= input.length) {
            break;
        }
        if (input[i+j] != 0) { 
            mask |= 1 << j;
            intermediate.push(input[i+j]);
        }
    } 

    encoded.push(mask);
    encoded.push(intermediate);    
}

console.log('encoded:');
console.log(encoded);

for (let i = 0; i < encoded.length; i += 2) {
    let mask = encoded[i];
    let intermediate = encoded[i+1];

    for (let j = 0; j < MASK_LENGTH; j++) {
        if (mask & (1 << j)) {
            let val = intermediate.shift()
            decoded.push(val);
        } else {
            decoded.push(0);
        }
    } 
}

console.log('decoded:');
console.log(decoded);
