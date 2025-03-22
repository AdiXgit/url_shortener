async function shortenUrl() {
    let longUrl = document.getElementById("longUrl").value;
    
    let response = await fetch("http://localhost:8080/shorten", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ url: longUrl })
    });

    let data = await response.json();
    document.getElementById("result").innerText = "Shortened URL: " + data.short_url;
}

async function expandUrl() {
    let shortUrl = document.getElementById("shortUrl").value;

    let response = await fetch(`http://localhost:8080/expand?short_url=${shortUrl}`);
    let data = await response.json();
    
    document.getElementById("result").innerText = "Expanded URL: " + data.long_url;
}
