//define buttons in index by their profiles
const prof1 = document.getElementById('profile1');
const prof2 = document.getElementById('profile2');
const prof3 = document.getElementById('profile3');

prof1.addEventListener('click', function(e) {
    console.log('Profile 1 btn pressed');
    fetch('/p1p', {method: 'POST'})
        .then(function(response) {
      	    if(response.ok) {
        	console.log('Profile 1 successfully selected');
        	return;
      	    }
      	    throw new Error('Profile 1 request failed.');
    	})
    	.catch(function(error) {
      	    console.log(error);
    	});

});

prof2.addEventListener('click', function(e) {
    console.log('Profile 2 button pressed');
    fetch('/p2p', {method: 'POST'})
        .then(function(response) {
      	    if(response.ok) {
        	console.log('Profile 2 successfully selected');
        	return;
      	    }
      	    throw new Error('Profile 2 request failed.');
    	})
    	.catch(function(error) {
      	    console.log(error);
    	});

});

prof3.addEventListener('click', function(e) {
    console.log('Profile 3 button pressed');
    fetch('/p3p', {method: 'POST'})
        .then(function(response) {
      	    if(response.ok) {
        	console.log('Profile 3 successfully selected');
        	return;
      	    }
      	    throw new Error('Profile 3 request failed.');
    	})
    	.catch(function(error) {
      	    console.log(error);
    	});

});


