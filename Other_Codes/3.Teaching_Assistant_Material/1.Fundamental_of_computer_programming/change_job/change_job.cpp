int q1(int val){
    int sum = 0;
    for(int i=1; i<=val/2; i++)
        if(val%i == 0)
            sum += i*i;

    return sum;
}
