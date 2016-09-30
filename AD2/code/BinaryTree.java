/*
 * HSR - Uebungen 'Algorithmen & Datenstrukturen 2'
 * Version: Tue Sep 22 15:10:35 CEST 2015
 */

package uebung02.ml.aufgabe01;

import java.util.Collection;
import java.util.LinkedList;

public class BinarySearchTree<K extends Comparable<? super K>, V> {

  protected Node root;

  public static class Entry<K, V> {

    private K key;
    private V value;

    public Entry(K key, V value) {
      this.key = key;
      this.value = value;
    }

    protected K setKey(K key) {
      K oldKey = this.key;
      this.key = key;
      return oldKey;
    }

    public K getKey() {
      return key;
    }

    public V setValue(V value) {
      V oldValue = this.value;
      this.value = value;
      return oldValue;
    }

    public V getValue() {
      return value;
    }

    @Override
    public String toString() {
      StringBuilder result = new StringBuilder();
      result.append("[").append(key).append("/").append(value).append("]");
      return result.toString();
    }

  } // End of class Entry

  protected class Node {

    private Entry<K, V> entry;
    private Node leftChild;
    private Node rightChild;

    public Node(Entry<K, V> entry) {
      this.entry = entry;
    }

    public Node(Entry<K, V> entry, Node leftChild, Node rightChild) {
      this.entry = entry;
      this.leftChild = leftChild;
      this.rightChild = rightChild;
    }

    public Entry<K, V> getEntry() {
      return entry;
    }

    public Entry<K, V> setEntry(Entry<K, V> entry) {
      Entry<K, V> oldEntry = entry;
      this.entry = entry;
      return oldEntry;
    }

    public Node getLeftChild() {
      return leftChild;
    }

    public void setLeftChild(Node leftChild) {
      this.leftChild = leftChild;
    }

    public Node getRightChild() {
      return rightChild;
    }

    public void setRightChild(Node rightChild) {
      this.rightChild = rightChild;
    }

  } // End of class Node

  protected class RemoveResult {

    private Node node;
    private Entry<K, V> entry;

    RemoveResult() {
    }

    public RemoveResult(Node node, Entry<K, V> entry) {
      this.node = node;
      this.entry = entry;
    }

    RemoveResult set(Node node) {
      this.node = node;
      return this;
    }

    public Node getNode() {
      return node;
    }

    public Entry<K, V> getEntry() {
      return entry;
    }

  }

  public Entry<K, V> insert(K key, V value) {
    Entry<K, V> newEntry = new Entry<K, V>(key, value);
    root = insert(root, newEntry);
    return newEntry;
  }

  protected Node insert(Node node, Entry<K, V> entry) {
    if (node == null)
      return newNode(entry);
    else if (entry.getKey().compareTo(node.getEntry().getKey()) <= 0) {
      node.leftChild = insert(node.leftChild, entry);
    } else { /* if (entry.key > node.key) */
      node.rightChild = insert(node.rightChild, entry);
    }
    return node;
  }

  /**
   * Factory-Method: Creates a new node.
   *
   * @param entry
   *          The entry to be inserted in the new node.
   * @return The new created node.
   */
  protected Node newNode(Entry<K, V> entry) {
    return new Node(entry);
  }

  public void clear() {
    root = null;
  }

  public Entry<K, V> find(K key) {
    Node result = find(root, key);
    if (result == null) {
      return null;
    } else {
      return result.getEntry();
    }
  }

  protected Node find(Node node, K key) {
    if (node == null) {
      return null;
    }
    if (key.compareTo(node.getEntry().getKey()) < 0) {
      return find(node.leftChild, key);
    }
    if (key.compareTo(node.getEntry().getKey()) > 0) {
      return find(node.rightChild, key);
    }
    return node;
  };

  /**
   * Returns a collection with all entries with key.
   *
   * @param key
   *          The key to be searched.
   * @return Collection of all entries found. An empty collection is returned if
   *         no entry with key is found.
   */
  public Collection<Entry<K, V>> findAll(K key) {
    Collection<Entry<K, V>> entries = new LinkedList<Entry<K, V>>();
    findAll(root, key, entries);
    return entries;
  }

  protected void findAll(Node node, K key, Collection<Entry<K, V>> entries) {
    if (node == null) {
      return;
    }
    if (key.compareTo(node.getEntry().getKey()) == 0) {
      entries.add(node.getEntry());
    }
    if (key.compareTo(node.getEntry().getKey()) <= 0) {
      findAll(node.leftChild, key, entries);
    }
    if (key.compareTo(node.getEntry().getKey()) >= 0) {
      findAll(node.rightChild, key, entries);
    }
  }

  /**
   * Returns a collection with all entries in inorder.
   *
   * @return Inorder-Collection of all entries.
   */
  public Collection<Entry<K, V>> inorder() {
    Collection<Entry<K, V>> coll = new LinkedList<Entry<K, V>>();
    inorder(root, coll);
    return coll;
  }

  protected void inorder(Node node, Collection<Entry<K, V>> coll) {
    if (node == null)
      return;
    inorder(node.getLeftChild(), coll);
    coll.add(node.getEntry());
    inorder(node.getRightChild(), coll);
  }

  /**
   * Prints the entries of the tree as a list in inorder to the console.
   */
  public void printInorder() {
    inorder().stream().forEach(e -> {
      System.out.print(e + " ");
    });
    System.out.println();
  }

  public Entry<K, V> remove(Entry<K, V> entry) {
    if (entry == null) {
      return null;
    }
    RemoveResult result = remove(root, entry);
    root = result.node;
    return result.entry;
  }

  protected RemoveResult remove(final Node node, final Entry<K, V> entry) {
    RemoveResult result = null;
    if (node == null) {
      return new RemoveResult(null, null);
    }
    if (entry.getKey().compareTo(node.getEntry().getKey()) < 0) {
      result = remove(node.leftChild, entry);
      node.leftChild = result.node;
      return result.set(node);
    } else if (entry.getKey().compareTo(node.getEntry().getKey()) > 0) {
      result = remove(node.rightChild, entry);
      node.rightChild = result.node;
      return result.set(node);
    } else {
      // Key found: is this the correct entry?
      if (node.getEntry() != entry) {
        // Searching for next entry with this key
        result = remove(node.leftChild, entry);
        node.leftChild = result.node;
        if (result.entry == null) {
          result = remove(node.rightChild, entry);
          node.rightChild = result.node;
        }
        return result.set(node);
      }
      // We have reachted the correct node.
      if (node.leftChild == null) {
        return new RemoveResult(node.rightChild, node.getEntry());
      }
      if (node.rightChild == null) {
        return new RemoveResult(node.leftChild, node.getEntry());
      }
      Entry<K, V> entryRemoved = node.getEntry();
      Node q = getParentNext(node);
      if (q == node) {
        node.setEntry(node.rightChild.getEntry());
        q.rightChild = q.rightChild.rightChild;
      } else {
        node.setEntry(q.leftChild.getEntry());
        q.leftChild = q.leftChild.rightChild;
      }
      return new RemoveResult(node, entryRemoved);
    }
  }

  /**
   * Search for the inorder successor.
   *
   * @param p
   *          The node for which the inorder successor shall be searched.
   * @return The parent-node(!) of the inorder successor.
   */
  protected Node getParentNext(Node p) {
    if (p.rightChild.leftChild != null) {
      p = p.rightChild;
      while (p.leftChild.leftChild != null)
        p = p.leftChild;
    }
    return p;
  }

  /**
   * The height of the tree.
   *
   * @return The actual height. -1 for an empty tree.
   */
  public int getHeight() {
    return getHeight(root);
  }

  protected int getHeight(Node p) {
    if (p == null)
      return -1;
    int rHeight = getHeight(p.rightChild);
    int lHeight = getHeight(p.leftChild);
    return (lHeight < rHeight ? rHeight : lHeight) + 1;
  }

  public int size() {
    return size(root);
  }

  protected int size(Node n) {
    if (n == null) {
      return 0;
    }
    return size(n.leftChild) + size(n.rightChild) + 1;
  }

  public boolean isEmpty() {
    return size() == 0;
  }

  public static void main(String[] args) {

    // Example from lecture "Löschen (IV/IV)":
    //BinarySearchTree<Integer, String> bts = new BinarySearchTree<Integer, String>();
    BinarySearchTree<Integer, String> bts = new BinarySearchTreeGVS<Integer, String>();
    System.out.println("Inserting:");
    bts.insert(1, "Str1");
    bts.printInorder();
    bts.insert(3, "Str3");
    bts.printInorder();
    bts.insert(2, "Str2");
    bts.printInorder();
    bts.insert(8, "Str8");
    bts.printInorder();
    bts.insert(9, "Str9");
    bts.insert(6, "Str6");
    bts.insert(5, "Str5");
    bts.printInorder();

    System.out.println("Removeing 3:");
    Entry<Integer, String> entry = bts.find(3);
    System.out.println(entry);
    bts.remove(entry);
    bts.printInorder();

    if (bts instanceof BinarySearchTreeGVS) {
      ((BinarySearchTreeGVS<Integer, String>)bts).gvsTree.disconnect();
    }

  }

  /* Session-Log:

  Inserting:
  [1/Str1]
  [1/Str1] [3/Str3]
  [1/Str1] [2/Str2] [3/Str3]
  [1/Str1] [2/Str2] [3/Str3] [8/Str8]
  [1/Str1] [2/Str2] [3/Str3] [5/Str5] [6/Str6] [8/Str8] [9/Str9]
  Removeing 3:
  [3/Str3]
  [1/Str1] [2/Str2] [5/Str3] [6/Str6] [8/Str8] [9/Str9]

  */


} // End of class BinarySearchTree
