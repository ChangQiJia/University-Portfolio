/*
 * CSCI 213 Assignment 2 
--------------------------
 * File name: Cards.java
 * Author : Chang Qi Jia 
 * Student Number : 5280618 09
 * Description : Cards Class
 */

import java.util.*; 
import java.io.*; 

public class Cards {
    
    private String suits; 
    private String name;
    
    Cards (String Suits, String Name)
    {
        this.suits = Suits;
        this.name = Name; 
    }
    
    public String getSuits ()
    {
        return suits;
    }
    
    public String getName () 
    {
        return name; 
    }
    
    public String toString () 
    {
        return ("<" + suits + name + "> ");
    }
}
