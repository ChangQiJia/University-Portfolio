/*
* CSCI213 Assignment 3
* --------------------------
* File name: ComputerPlayer.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: ComputerPlayer
*/

public class ComputerPlayer extends GamePlayer {

	private BrainInterface brainInterface;
        private int score; 
	
	public ComputerPlayer(String loginName, String hashedPassword, int points,BrainInterface brainInterface) {
		super(loginName, hashedPassword, points);
		this.brainInterface = brainInterface;
	}

	public int getFirstCardNumber(int maxNumberOfCard){
		
		int cardNumber1 = brainInterface.getFirstCardNumber(maxNumberOfCard);
		return cardNumber1;
	}

	public int getSecondCardNumber(int maxNumberOfCard, int cardNumber1){
		int cardNumber2 = brainInterface.getSecondCardNumber(maxNumberOfCard,cardNumber1);
		return cardNumber2;
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
	
}
