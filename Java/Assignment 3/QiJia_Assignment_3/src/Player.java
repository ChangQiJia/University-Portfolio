/*
* CSCI213 Assignment 3
* --------------------------
* File name: Player.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: (A brief description of this class)
*/

public class Player extends User {
    
    private int points;
    
    public Player(String loginName,String hashedPassword,int points)
    {
        super(loginName,hashedPassword);
        this.points=points;
    }
    
}
