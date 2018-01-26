/*
* CSCI213 Assignment 4
* --------------------------
* File name: Winner.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: Object to store winner of game
*/

import java.io.*; 
import java.util.*; 
import java.net.*; 
import javax.swing.*; 
import java.awt.event.*; 
import java.awt.*; 

public class Winner implements Serializable{
        private String winnerName; 
        
        Winner (String name)
        {
            winnerName = name; 
        }
        
        public String getName ()
        {
            return winnerName;
        }
}
