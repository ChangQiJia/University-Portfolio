/*
* CSCI213 Assignment 4
* --------------------------
* File name: Deck.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: Deck
*/

import java.util.*;
import java.io.*;

public class Deck implements Serializable{

	private ArrayList<Card> cards;

	public Deck() {

		cards = new ArrayList<Card>();

		String[] suits = { "Heart", "Diamond" };

		Card card = new Card(suits[0], "Ace", 1);
		cards.add(card);
		card = new Card(suits[1], "Ace", 1);
		cards.add(card);

		card = new Card(suits[0], "Jack", 10);
		cards.add(card);

		card = new Card(suits[1], "Jack", 10);
		cards.add(card);

		card = new Card(suits[0], "Queen", 10);
		cards.add(card);

		card = new Card(suits[1], "Queen", 10);
		cards.add(card);
                
                card = new Card(suits[0], "King", 10);
		cards.add(card);

		card = new Card(suits[1], "King", 10);
		cards.add(card);

	}

	public void showCards() {
		for (Card card : cards) {
			System.out.println(card);
		}
	}

	public Card dealCard() {
		return cards.remove(0);
	}

	public void appendCard(Card c) {
		cards.add(c);

	}

	public void appendCards(ArrayList<Card> cards) {
		shuffle(cards);
		for (Card c : cards)
			this.cards.add(c);

	}

	public void shuffle() {
		shuffle(cards);
	}

	public int getNumberOfCards() {
		return cards.size();
	}

	public void shuffle(ArrayList<Card> cards) {

		Random r = new Random();
		for (int i = 0; i < cards.size() * 1000; i++) {
			int a = r.nextInt(cards.size());
			int b = r.nextInt(cards.size());

			Card cardA = cards.get(a);
			Card cardB = cards.get(b);

			cards.set(a, cardB);
			cards.set(b, cardA);

		}

	}

	public static void main(String[] args) {

		Deck deck = new Deck();
		deck.showCards();
		deck.shuffle();
		deck.showCards();

	}

}
