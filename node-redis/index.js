const { createClient } = require('redis');

(async () => {
    const client = createClient({
        url: 'redis://localhost:6379'
    });

    client.on('error', (err) => console.log('Redis Client Error', err));
    
    await client.connect();
    
    let refTime = new Date();
    let count = 0;
    while(true) {
        const value = await client.get('demo1');
        let now = new Date();
        if(now.getSeconds() != refTime.getSeconds()) {
            console.log(now, value, count);
            refTime = now;
            count = 0;
        }
        count += 1;
    }
    

})().catch(e => {
    console.log(e);
});
