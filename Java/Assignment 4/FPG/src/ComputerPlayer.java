/*
* CSCI213 Assignment 4
* --------------------------
* File name: ComputerPlayer.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: ComputerPlayer
*/

public class ComputerPlayer implements Players{
     private int score; 
     private String loginName; 
     private int turn; 
	
	public ComputerPlayer(String loginName, int turn) {
		this.loginName = loginName; 
                this.turn = turn; 
	}

	public int getFirstCardNumber(int maxNumberOfCard)
        {
            
            int cardNo = 0; 
            
            return cardNo; 
	}

	public int getSecondCardNumber(int maxNumberOfCard, int cardNumber1)
        {
            int cardNo = 0; 
            
            return cardNo; 
	}
        
        public void addScore ()
        {
            score++; 
        }
        
        public int getScore() 
        {
            return score; 
        }
        
        public void setScore (int s)
        {
            score = s; 
        }
        
        public String getLoginName () 
        {
            return loginName;
        }
}
