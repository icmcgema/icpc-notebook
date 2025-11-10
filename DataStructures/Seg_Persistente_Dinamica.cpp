struct SEG{
    
    int create(){
        e.pb(0) ; d.pb(0) ; lazy.pb(0) ; sum.pb(0) ;
        return e.size()-1 ;  
    }

    int clone(int u){
        int v = create() ; 
        e[v] = e[u], d[v] = d[u] ; 
        lazy[v] = lazy[u] ; sum[v] = sum[u] ; 
        return v ;  
    }

    void apply(int u, int add, int len){
        sum[u] += add*len ; 
        lazy[u] += add ; 
    }

    void flush(int no, int i, int j){
        if(!lazy[no] || i == j || no >= e.size()) return ; 

        e[no] = clone(e[no]) ;  
        d[no] = clone(d[no]) ; 

        apply(e[no], lazy[no], meio-i+1);
        apply(d[no], lazy[no], j-meio) ; 

        lazy[no] = 0 ; 
    }

    int upd(int no, int i, int j, int a, int b, int val){
        if(i > j) return 0 ; 

        int neww = clone(no) ; 

        if(i > b || j < a) return neww ;
        
        if(a <= i && b >= j){
            apply(neww, val, j-i+1);
            return neww ; 
        }

        flush(neww, i, j) ; 

        if(!e[neww]) e[neww] = create(); 
        if(!d[neww]) d[neww] = create() ; 
        
        int aux1 = upd(e[neww], i, meio, a, b, val) ; 
        int aux2 = upd(d[neww], meio + 1, j, a, b, val) ; 

        e[neww] = aux1, d[neww] = aux2 ; 
        sum[neww] = sum[e[neww]] + sum[d[neww]]; 

        return neww ; 
    }

    int query(int pos, int i, int j, int l, int r, int carry){
        if(i > r || j < l) return 0 ; 

        if(l <= i && r >= j) return sum[pos] + (carry*(j-i+1)); 

        int newcarry = carry + lazy[pos] ; 

        return query(e[pos], i, meio, l, r, newcarry) + query(d[pos], meio + 1, j, l, r, newcarry) ; 
    }

}; 
