use nalgebra::{DMatrix};

fn main() {
    println!("Hamming code(7, 4) without matrices");
    let input: Vec<i32> = vec![0, 0, 0, 1];
    println!("Input: {:?}", input);
    // let input: Vec<i32> = vec![1, 0, 0, 1];
    let output = hamming_coder_7_4(input.clone());
    // println!("Input {:?}", input);
    // println!("Output {:?}", output);
    // let decoded_output = hamming_decoder_7_4(output.clone());
    // println!("Decoded {:?}", decoded_output);
    // let input: Vec<i32> = vec![0, 0, 0, 1];
    // let output = hamming_coder_7_4(input.clone());
    // println!("Input {:?}", input);
    // println!("Output {:?}", output);
    // let decoded_output = hamming_decoder_7_4(output.clone());
    // println!("Decoded {:?}", decoded_output);
    for i in 1..8 {
        let mut output_with_error = output.clone();
        output_with_error[i - 1] ^= 1;
        print!("position {} ", i);
        let decoded_output = hamming_decoder_7_4(output_with_error.clone());
        println!(" decoded {:?}", decoded_output);
    }
    println!("\nHamming code(7, 4) with matrices");
    let input: Vec<i32> = vec![1, 0, 1, 0];
    println!("Input: {:?}", input);
    let output = hamming_coder_7_4_matrix(input.clone());
    for i in 1..8 {
        let mut output_with_error = output.clone();
        output_with_error[i - 1] ^= 1;
        print!("position {} ", i);
        let decoded_output = hamming_decoder_7_4_matrix(output_with_error.clone());
        println!(" decoded {:?}", decoded_output);
    }
    println!("\nHamming code(15, 11) with matrices");
    let input: Vec<i32> = vec![0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0];
    println!("Input: {:?}", input);
    let output = hamming_coder_15_11(input.clone());
    for i in 1..15 {
        let mut output_with_error = output.clone();
        output_with_error[i - 1] ^= 1;
        print!("position {} ", i);
        let decoded_output = hamming_decoder_15_11(output_with_error.clone());
        println!(" decoded {:?}", decoded_output);
    }
}

fn hamming_coder_7_4(input: Vec<i32>) -> Vec<i32> {
    let mut output = vec![0; 7];

    // output |= (input & 1) << 2; // data bit 1 to 3
    // output |= (input & 2) << 3; // data bit 2 to 5
    // output |= (input & 4) << 3; // data bit 3 to 6
    // output |= (input & 8) << 3; // data bit 4 to 7
    output[2] = input[0];
    output[4] = input[1];
    output[5] = input[2];
    output[6] = input[3];

    // let p1 = ((output >> 2) & 1) ^ ((output >> 4) & 1) ^ ((output >> 6) & 1); // parity bit at 1
    // let p2 = ((output >> 2) & 1) ^ ((output >> 5) & 1) ^ ((output >> 6) & 1); // parity bit at 2
    // let p4 = ((output >> 4) & 1) ^ ((output >> 5) & 1) ^ ((output >> 6) & 1); // parity bit at 4

    let p1 = output[2] ^ output[4] ^ output[6];
    let p2 = output[2] ^ output[5] ^ output[6];
    let p4 = output[4] ^ output[5] ^ output[6];

    // output |= p1 << 0;
    // output |= p2 << 1;
    // output |= p4 << 3;

    output[0] = p1;
    output[1] = p2;
    output[3] = p4;

    output
}

fn hamming_decoder_7_4(input: Vec<i32>) -> Vec<i32> {
    // let p1 = ((input >> 0) & 1) ^ ((input >> 2) & 1) ^ ((input >> 4) & 1) ^ ((input >> 6) & 1);
    // let p2 = ((input >> 1) & 1) ^ ((input >> 2) & 1) ^ ((input >> 5) & 1) ^ ((input >> 6) & 1);
    // let p4 = ((input >> 3) & 1) ^ ((input >> 4) & 1) ^ ((input >> 5) & 1) ^ ((input >> 6) & 1);
    let p1 = input[0] ^ input[2] ^ input[4] ^ input[6];
    let p2 = input[1] ^ input[2] ^ input[5] ^ input[6];
    let p4 = input[3] ^ input[4] ^ input[5] ^ input[6];

    let syndrome: usize = ((p4 << 2) | (p2 << 1) | p1) as usize;
    print!("syndrome: {}", syndrome);
    let mut corrected_input = input;
    if syndrome != 0 {
        corrected_input[syndrome - 1] ^= 1;
    }

    // let mut output = 0;
    // output |= (corrected_input >> 2) & 1;
    // output |= (corrected_input >> 3) & 2;
    // output |= (corrected_input >> 3) & 4;
    // output |= (corrected_input >> 3) & 8;
    vec![corrected_input[2], corrected_input[4], corrected_input[5], corrected_input[6]]
}

fn hamming_coder_7_4_matrix(input: Vec<i32>) -> Vec<i32> {
    let I = DMatrix::<i32>::identity(4, 4);
    let P =DMatrix::from_row_slice(4, 3, &vec![
        1, 1, 0,
        1, 0, 1,
        0, 1, 1,
        1, 1, 1
    ]);
    let mut G = DMatrix::<i32>::zeros(4, 7);
    G.view_mut((0, 0), (4, 3)).copy_from(&P);
    G.view_mut((0, 3), (4, 4)).copy_from(&I);
    let b = DMatrix::from_column_slice(1, 4, &input);
    let c = b * G;
    c.map(|x| x % 2).as_slice().to_vec()
}

fn hamming_decoder_7_4_matrix(input: Vec<i32>) -> Vec<i32> {
    let I = DMatrix::<i32>::identity(3, 3);
    let P = DMatrix::from_row_slice(4, 3, &vec![
        1, 1, 0,
        1, 0, 1,
        0, 1, 1,
        1, 1, 1
    ]).transpose();
    let mut H = DMatrix::<i32>::zeros(3, 7);
    H.view_mut((0, 0), (3, 3)).copy_from(&I);
    H.view_mut((0, 3), (3, 4)).copy_from(&P);
    let c = DMatrix::from_column_slice(1, 7, &input);
    let mut s = c.clone() * H.transpose();
    s = s.map(|x| x % 2);
    let syndrome_vec = s.as_slice().to_vec();
    let mut syndrome = 0;
    for (i, &bit) in syndrome_vec.iter().enumerate() {
        syndrome += (bit as usize) << i;
    }
    print!("syndrome: {} ", syndrome);
    let mut corrected_c = c.as_slice().to_vec();
    if syndrome != 0 {
        corrected_c[syndrome - 1] ^= 1;
    }
    vec![corrected_c[3], corrected_c[4], corrected_c[5], corrected_c[6]]
}

fn hamming_coder_15_11(input: Vec<i32>) -> Vec<i32> {
    let I = DMatrix::<i32>::identity(11, 11);
    let P = DMatrix::from_row_slice(11, 4, &vec![
        1, 1, 0, 0,
        1, 0, 1, 0,
        0, 1, 1, 0,
        1, 1, 1, 0,
        1, 0, 0, 1,
        0, 1, 0, 1,
        1, 1, 0, 1,
        0, 0, 1, 1,
        1, 0, 1, 1,
        0, 1, 1, 1,
        1, 1, 1, 1
    ]);
    let mut G = DMatrix::<i32>::zeros(11, 15);
    G.view_mut((0, 0), (11, 4)).copy_from(&P);
    G.view_mut((0, 4), (11, 11)).copy_from(&I);
    let b = DMatrix::from_column_slice(1, 11, &input);
    let c = b * G;
    c.map(|x| x % 2).as_slice().to_vec()
}

fn hamming_decoder_15_11(input: Vec<i32>) -> Vec<i32> {
    let I = DMatrix::<i32>::identity(4, 4);
    let P = DMatrix::from_row_slice(11, 4, &vec![
        1, 1, 0, 0,
        1, 0, 1, 0,
        0, 1, 1, 0,
        1, 1, 1, 0,
        1, 0, 0, 1,
        0, 1, 0, 1,
        1, 1, 0, 1,
        0, 0, 1, 1,
        1, 0, 1, 1,
        0, 1, 1, 1,
        1, 1, 1, 1
    ]).transpose();
    let mut H = DMatrix::<i32>::zeros(4, 15);
    H.view_mut((0, 0), (4, 4)).copy_from(&I);
    H.view_mut((0, 4), (4, 11)).copy_from(&P);
    let c = DMatrix::from_column_slice(1, 15, &input);
    let mut s = c.clone() * H.transpose();
    s = s.map(|x| x % 2);
    let syndrome_vec = s.as_slice().to_vec();
    let mut syndrome = 0;
    for (i, &bit) in syndrome_vec.iter().enumerate() {
        syndrome += (bit as usize) << i;
    }
    print!("syndrome: {} ", syndrome);
    let mut corrected_c = c.as_slice().to_vec();
    if syndrome != 0 {
        corrected_c[syndrome - 1] ^= 1;
    }
    vec![corrected_c[4], corrected_c[5], corrected_c[6], corrected_c[7],
        corrected_c[8], corrected_c[9], corrected_c[10], corrected_c[11],
        corrected_c[12], corrected_c[13], corrected_c[14]]
}