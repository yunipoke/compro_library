struct Eratosthenes {
    vector<int> isp,minfactor,myprime,moebius;

    Eratosthenes (int n) : isp(n+1,1),minfactor(n+1,__INT_MAX__),moebius(n+1,1){

        isp[0] = isp[1] = 0;
        minfactor[0] = 0;minfactor[1] = 1;

        for(int p = 2;p <= n;p++){
            if(!isp[p]) continue;
            minfactor[p] = p;
            moebius[p] = -1;
            myprime.push_back(p);

            for(int q = 2*p;q <= n;q += p){
                isp[q] = false;

                if(!((q/p)%p)) moebius[q] = 0;
                else moebius[q] = -moebius[q];


                minfactor[q] = min(minfactor[q],p);
            }
        }
    }

    vector<pair<int,int>> prime_factorize(int n) {
        vector<pair<int,int>> res;
        while(n-1){

            int p = minfactor[n];
            int exp = 0;

            while(minfactor[n] == p){
                n /= p;
                exp ++;
            }

            res.push_back(make_pair(p,exp));
        }

        return res;
    }

    vector<int> divisors(int n){
        vector<int> res;
        res.push_back(1);

        auto pf = prime_factorize(n);

        for(auto [p,e]:pf){
            int s = (int)res.size();

            for(int i = 0;i < s;i++){
                int v = 1;
                for(int j = 0;j < e;j++){
                    v *= p;
                    res.push_back(res[i]*v);
                }
            }
        }

        return res;
    }
};