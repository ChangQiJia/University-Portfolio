/*
* CSCI213 Assignment 3
* --------------------------
* File name: Card.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: Card
*/

import javax.swing.*; 
import java.awt.*; 

public class Card extends JPanel{

	private String suit;
	private String name;
	private int value;
        private JLabel cardLabel; 
        private ImageIcon cardImage = new ImageIcon ("CardBack.png"); 
        private boolean activeMouse = true; 

	public Card(String s, String n, int v) {
		
                suit = s;
		name = n;
		value = v;
                
                cardLabel = new JLabel (); 
                cardLabel.setIcon(cardImage);
                
                add (cardLabel);
                
                setPreferredSize (new Dimension (200,400)); 
	}

	public String getSuit() {
		return suit;
	}

	public String getName() {
		return name;
	}

	public int getValue() {
		return value;
	}

	public String toString() {
		return "<" + suit + " " + name + ">";
	}
        
        public void changeImage (String imageName) 
        {
            cardLabel.setIcon(new ImageIcon (imageName));
        }
        
        public boolean active () 
        {
            return activeMouse;
        }
        
        public void switchOffMouse () 
        {
            activeMouse = false;
        }
        
        public void switchOnMouse () 
        {
            activeMouse = true;
        }

}
