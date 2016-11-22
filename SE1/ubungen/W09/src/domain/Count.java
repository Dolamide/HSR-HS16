package domain;

import java.util.Observable;

public class Count extends Observable {
    private int value = 0;

    public void increment() {
        value = value + 1;
        setChanged();
        notifyObservers();
    }

    public int getValue() {
        return value;
    }
}