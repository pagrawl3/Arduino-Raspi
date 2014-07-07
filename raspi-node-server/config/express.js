var express = require('express'),
	path 		= require('path'),
	rootPath	= path.normalize(__dirname + '/..');

module.exports = function (app) {

	app.set('showStackError', true)
	app.use(express.compress());
	//Setup the public serving directory
	app.use(express.staticCache());
	app.use(express.static(rootPath + '/assets/public', {maxAge: 864000000}));
	// app.use(express.favicon(rootPath + '/assets/public/img/favicon.ico')); 
	//Set the view templating engine and the views directory
	app.set('views', rootPath + '/app/views');
	app.set('view engine', 'jade');

	//Default app configurations
	app.configure(function() {
		//bodyParser
		app.use(express.json());
		app.use(express.urlencoded());
		app.use(express.methodOverride());
		//Use the router
		app.use(app.router);
	})
}