/*
* CSCI213 Assignment 4
* --------------------------
* File name: HumanPlayer.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: Human Player
*/

import java.io.*; 

public class HumanPlayer implements Players{
    
    private int score = 0; 
    private String loginName; 
    private int turn; 
    
    HumanPlayer (String loginName, int turn)
    {
        this.loginName = loginName; 
        this.turn = turn; 
    }
    
    public int getScore() 
        {
		return score; 
	}
    
    public void addScore ()
        {
            score++; 
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
