class RLEIterator {
    int idx;
    int[] encoding;

    public RLEIterator(int[] encoding) {
        this.encoding = encoding;
        this.idx = 0;
    }
    
    public int next(int n) {
        for (int i = idx; i < encoding.length; i += 2) {
            if (n <= encoding[i]) {
                encoding[i] -= n;
                return encoding[i + 1];
            } else {
                n -= encoding[i];
                idx += 2;
            }
        }
        return -1;
    }
}

/**
 * Your RLEIterator object will be instantiated and called as such:
 * RLEIterator obj = new RLEIterator(encoding);
 * int param_1 = obj.next(n);
 */
