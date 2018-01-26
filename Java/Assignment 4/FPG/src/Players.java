/*
* CSCI213 Assignment 4
* --------------------------
* File name: Players.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: Interface for computer and human player to reference to
*/

import java.util.ArrayList;
import java.io.*; 


public interface Players extends Serializable{
        
        public int getScore();
        public void addScore(); 
        public void setScore (int s);
        public String getLoginName ();
}
