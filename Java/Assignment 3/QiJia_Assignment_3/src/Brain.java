/*
* CSCI213 Assignment 3
* --------------------------
* File name: Brain.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: AI
*/

import java.util.Random;

public class Brain implements BrainInterface{

	private Random r;
	
	public Brain(){
		r = new Random();
	}
	
	public int getFirstCardNumber(int maxNumberOfCard){
		return r.nextInt(maxNumberOfCard)+1;
	}

	public int getSecondCardNumber(int maxNumberOfCard, int cardNumber1){
	
		int num = 0;
		while(true){
			num = getFirstCardNumber(maxNumberOfCard);
			if(num!=cardNumber1) break;
		}
		
		return num;
	}
	
}
