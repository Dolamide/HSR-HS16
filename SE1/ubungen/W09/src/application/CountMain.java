package application;

import gui.View;
import domain.Count;

public class CountMain {
    public static void main(String[] args) {
        Count c = new Count();
        View v = new View(c);
        View v2 = new View(c);
    }
}